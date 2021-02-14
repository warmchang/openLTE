/*******************************************************************************

    Copyright 2013-2015, 2017, 2021 Ben Wojtowicz
    Copyright 2014 Andrew Murphy (SIB13 printing)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************

    File: LTE_fdd_dl_scan_interface.cc

    Description: Contains all the implementations for the LTE FDD DL Scanner
                 interface.

    Revision History
    ----------    -------------    --------------------------------------------
    02/26/2013    Ben Wojtowicz    Created file
    07/21/2013    Ben Wojtowicz    Added support for decoding SIBs.
    06/15/2014    Ben Wojtowicz    Added PCAP support.
    09/19/2014    Andrew Murphy    Added SIB13 printing.
    11/01/2014    Ben Wojtowicz    Using the latest LTE library.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t.
    07/29/2017    Ben Wojtowicz    Using the latest tools library.
    02/14/2021    Ben Wojtowicz    Massive reformat and using the new RRC
                                   library.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_scan_interface.h"
#include "liblte_mcc_mnc_list.h"
#include "libtools_helpers.h"
#include <assert.h>
#include <arpa/inet.h>

/*******************************************************************************
                              DEFINES
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              GLOBAL VARIABLES
*******************************************************************************/


/*******************************************************************************
                              CLASS IMPLEMENTATIONS
*******************************************************************************/

LTE_fdd_dl_scan_interface::LTE_fdd_dl_scan_interface() :
    flowgraph{NULL}, band_token{"band"}, dl_earfcn_list_token{"dl_earfcn_list"},
    repeat_token{"repeat"}, enable_pcap_token{"enable_pcap"}, pcap_fd{NULL},
    ctrl_socket{NULL}, band{LIBLTE_INTERFACE_BAND_1}, dl_earfcn_list_idx{0},
    ctrl_connected{false}, repeat{true}, enable_pcap{false}, shutdown{false}
{
    // Variables
    for(int32 i=0; i<(liblte_interface_last_dl_earfcn[band] -
                      liblte_interface_first_dl_earfcn[band] + 1); i++)
        dl_earfcn_list.push_back(liblte_interface_first_dl_earfcn[band] + i);
    current_dl_earfcn = dl_earfcn_list[0];

    open_pcap_fd();

    start_ctrl_port();
}

LTE_fdd_dl_scan_interface::~LTE_fdd_dl_scan_interface()
{
    stop_ctrl_port();

    if(flowgraph != NULL)
        delete flowgraph;

    fclose(pcap_fd);
}

void LTE_fdd_dl_scan_interface::start_ctrl_port()
{
    std::lock_guard<std::mutex>       lock(ctrl_mutex);
    LIBTOOLS_SERVER_SOCKET_ERROR_ENUM error;

    if(NULL != ctrl_socket)
        return;

    libtools_server_socket_receive_callback receive_cb(
        &libtools_server_socket_receive_callback::wrapper<LTE_fdd_dl_scan_interface, &LTE_fdd_dl_scan_interface::handle_ctrl_msg>,
        this);
    libtools_server_socket_connect_disconnect_callback connect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_fdd_dl_scan_interface, &LTE_fdd_dl_scan_interface::handle_ctrl_connect>,
        this);
    libtools_server_socket_connect_disconnect_callback disconnect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_fdd_dl_scan_interface, &LTE_fdd_dl_scan_interface::handle_ctrl_disconnect>,
        this);
    libtools_server_socket_error_callback error_cb(
        &libtools_server_socket_error_callback::wrapper<LTE_fdd_dl_scan_interface, &LTE_fdd_dl_scan_interface::handle_ctrl_error>,
        this);

    ctrl_socket = new libtools_server_socket(LTE_FDD_DL_SCAN_CTRL_PORT, receive_cb, connect_cb,
                                             disconnect_cb, error_cb, error);
    if(error == LIBTOOLS_SERVER_SOCKET_ERROR_NONE)
        return;
    printf("ERROR: Couldn't open ctrl_socket %u\n", error);
    ctrl_socket = NULL;
}

void LTE_fdd_dl_scan_interface::stop_ctrl_port()
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(NULL == ctrl_socket)
        return;

    delete ctrl_socket;
    ctrl_socket = NULL;
}

void LTE_fdd_dl_scan_interface::send_ctrl_msg(std::string msg)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(!ctrl_connected)
        return;

    ctrl_socket->send(msg + "\n", ctrl_sock_fd);
}

void LTE_fdd_dl_scan_interface::send_channel_found_begin_msg(float                         freq_offset,
                                                             uint32                        N_id_cell,
                                                             const MasterInformationBlock &mib,
                                                             uint32                        sfn,
                                                             uint8                         N_ant)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);
    std::string                 tmp_msg;

    if(!ctrl_connected)
        return;

    tmp_msg  = "info channel_found_begin ";
    tmp_msg += "freq=" + std::to_string(liblte_interface_dl_earfcn_to_frequency(current_dl_earfcn)) + " ";
    tmp_msg += "dl_earfcn=" + std::to_string(current_dl_earfcn) + " ";
    tmp_msg += "freq_offset=" + std::to_string(freq_offset) + " ";
    tmp_msg += "phys_cell_id=" + std::to_string(N_id_cell) + " ";
    tmp_msg += "sfn=" + std::to_string(sfn) + " ";
    tmp_msg += "n_ant=" + std::to_string(N_ant) + " ";
    tmp_msg += mib.ToString(0);
    tmp_msg += "\n";
    ctrl_socket->send(tmp_msg, ctrl_sock_fd);
}

void LTE_fdd_dl_scan_interface::send_sib1_msg(float                              freq_offset,
                                              uint32                             N_id_cell,
                                              const SystemInformationBlockType1 &sib1,
                                              uint32                             sfn)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);
    std::string                 tmp_msg;

    if(!ctrl_connected)
        return;

    tmp_msg  = "info sib1_decoded ";
    tmp_msg += "freq=" + std::to_string(liblte_interface_dl_earfcn_to_frequency(current_dl_earfcn)) + " ";
    tmp_msg += "dl_earfcn=" + std::to_string(current_dl_earfcn) + " ";
    tmp_msg += "freq_offset=" + std::to_string(freq_offset) + " ";
    tmp_msg += "phys_cell_id=" + std::to_string(N_id_cell) + " ";
    tmp_msg += "sfn=" + std::to_string(sfn) + " ";
    tmp_msg += sib1.ToString(0);

    ctrl_socket->send(tmp_msg, ctrl_sock_fd);
}

void LTE_fdd_dl_scan_interface::send_sib_msg(float                           freq_offset,
                                             uint32                          N_id_cell,
                                             const SystemInformation_r8_IEs &sib,
                                             uint32                          sfn)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);
    std::string                 tmp_msg;

    if(!ctrl_connected)
        return;

    tmp_msg  = "info sib_decoded ";
    tmp_msg += "freq=" + std::to_string(liblte_interface_dl_earfcn_to_frequency(current_dl_earfcn)) + " ";
    tmp_msg += "dl_earfcn=" + std::to_string(current_dl_earfcn) + " ";
    tmp_msg += "freq_offset=" + std::to_string(freq_offset) + " ";
    tmp_msg += "phys_cell_id=" + std::to_string(N_id_cell) + " ";
    tmp_msg += "sfn=" + std::to_string(sfn) + " ";
    tmp_msg += sib.ToString(0);

    ctrl_socket->send(tmp_msg, ctrl_sock_fd);
}

void LTE_fdd_dl_scan_interface::send_channel_found_end_msg(float  freq_offset,
                                                           uint32 N_id_cell)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);
    std::string                 tmp_msg;

    if(!ctrl_connected)
        return;

    tmp_msg  = "info channel_found_end ";
    tmp_msg += "freq=" + std::to_string(liblte_interface_dl_earfcn_to_frequency(current_dl_earfcn)) + " ";
    tmp_msg += "dl_earfcn=" + std::to_string(current_dl_earfcn) + " ";
    tmp_msg += "freq_offset=" + std::to_string(freq_offset) + " ";
    tmp_msg += "phys_cell_id=" + std::to_string(N_id_cell) + " ";
    tmp_msg += "\n";
    ctrl_socket->send(tmp_msg, ctrl_sock_fd);
}

void LTE_fdd_dl_scan_interface::send_channel_not_found_msg()
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);
    std::string                 tmp_msg;

    if(!ctrl_connected)
        return;

    tmp_msg  = "info channel_not_found ";
    tmp_msg += "freq=" + std::to_string(liblte_interface_dl_earfcn_to_frequency(current_dl_earfcn)) + " ";
    tmp_msg += "dl_earfcn=" + std::to_string(current_dl_earfcn) + " ";
    tmp_msg += "\n";
    ctrl_socket->send(tmp_msg, ctrl_sock_fd);
}

void LTE_fdd_dl_scan_interface::open_pcap_fd()
{
    uint32 magic_number  = 0xa1b2c3d4;
    uint32 timezone      = 0;
    uint32 sigfigs       = 0;
    uint32 snap_len      = (LIBLTE_MAX_MSG_SIZE/4);
    uint32 dlt           = 147;
    uint16 major_version = 2;
    uint16 minor_version = 4;

    pcap_fd = fopen("/tmp/LTE_fdd_dl_scan.pcap", "w");

    fwrite(&magic_number,  sizeof(magic_number),  1, pcap_fd);
    fwrite(&major_version, sizeof(major_version), 1, pcap_fd);
    fwrite(&minor_version, sizeof(minor_version), 1, pcap_fd);
    fwrite(&timezone,      sizeof(timezone),      1, pcap_fd);
    fwrite(&sigfigs,       sizeof(sigfigs),       1, pcap_fd);
    fwrite(&snap_len,      sizeof(snap_len),      1, pcap_fd);
    fwrite(&dlt,           sizeof(dlt),           1, pcap_fd);
}

void LTE_fdd_dl_scan_interface::send_pcap_msg(uint32                 rnti,
                                              uint32                 current_tti,
                                              LIBLTE_BIT_MSG_STRUCT &msg)
{
    if(!enable_pcap)
        return;

    // Get approximate time stamp
    struct timeval  time;
    struct timezone time_zone;
    gettimeofday(&time, &time_zone);

    // Radio Type
    uint8 pcap_c_hdr[15];
    pcap_c_hdr[0] = 1;

    // Direction
    pcap_c_hdr[1] = 1; // DL only for now

    // RNTI Type
    if(0xFFFFFFFF == rnti)
    {
        pcap_c_hdr[2] = 0;
    }else{
        pcap_c_hdr[2] = 4;
    }

    // RNTI Tag and RNTI
    pcap_c_hdr[3] = 2;
    uint16 tmp    = htons((uint16)rnti);
    memcpy(&pcap_c_hdr[4], &tmp, sizeof(uint16));

    // UEID Tag and UEID
    pcap_c_hdr[6] = 3;
    pcap_c_hdr[7] = 0;
    pcap_c_hdr[8] = 0;

    // SUBFN Tag and SUBFN
    pcap_c_hdr[9] = 4;
    tmp           = htons((uint16)(current_tti%10));
    memcpy(&pcap_c_hdr[10], &tmp, sizeof(uint16));

    // CRC Status Tag and CRC Status
    pcap_c_hdr[12] = 7;
    pcap_c_hdr[13] = 1;

    // Payload Tag
    pcap_c_hdr[14] = 1;

    // Payload
    uint8  pcap_msg[LIBLTE_MAX_MSG_SIZE/8];
    uint32 idx    = 0;
    pcap_msg[idx] = 0;
    for(uint32 i=0; i<msg.N_bits; i++)
    {
        pcap_msg[idx] <<= 1;
        pcap_msg[idx]  |= msg.msg[i];
        if((i % 8) == 7)
        {
            idx++;
            pcap_msg[idx] = 0;
        }
    }

    // Total Length
    uint32 length = 15 + idx;

    // Write Data
    fwrite(&time.tv_sec,  sizeof(uint32), 1,   pcap_fd);
    fwrite(&time.tv_usec, sizeof(uint32), 1,   pcap_fd);
    fwrite(&length,       sizeof(uint32), 1,   pcap_fd);
    fwrite(&length,       sizeof(uint32), 1,   pcap_fd);
    fwrite(pcap_c_hdr,    sizeof(uint8),  15,  pcap_fd);
    fwrite(pcap_msg,      sizeof(uint8),  idx, pcap_fd);
}

void LTE_fdd_dl_scan_interface::handle_ctrl_msg(const std::string msg,
                                                const int32       sock_fd)
{
    if(0 == msg.find("shutdown"))
    {
        send_ctrl_msg("ok");
        shutdown = true;
        return;
    }
    if(0 == msg.find("read"))
        return handle_read(msg);
    if(0 == msg.find("write"))
        return handle_write(msg);
    if(0 == msg.find("start"))
        return handle_start();
    if(0 == msg.find("stop"))
        return handle_stop();
    if(0 == msg.find("help"))
        return handle_help();
    send_ctrl_msg("fail invalid command");
}

void LTE_fdd_dl_scan_interface::handle_ctrl_connect(const int32 sock_fd)
{
    ctrl_mutex.lock();
    ctrl_connected = true;
    ctrl_sock_fd   = sock_fd;
    ctrl_mutex.unlock();

    send_ctrl_msg("*** LTE FDD DL SCAN ***");
    send_ctrl_msg("Type help to see a list of commands");
}

void LTE_fdd_dl_scan_interface::handle_ctrl_disconnect(const int32 sock_fd)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    ctrl_connected = false;
}

void LTE_fdd_dl_scan_interface::handle_ctrl_error(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err)
{
    printf("ERROR: ctrl_socket error %u\n", err);
    assert(0);
}

void LTE_fdd_dl_scan_interface::handle_read(std::string msg)
{
    if(0 != msg.find("read "))
        return send_ctrl_msg("fail invalid read command");
    std::string param = msg.substr(5);
    if(0 == param.find(band_token))
        return send_ctrl_msg("ok " + (std::string)liblte_interface_band_text[band]);
    if(0 == param.find(dl_earfcn_list_token))
        return read_dl_earfcn_list();
    if(0 == param.find(repeat_token))
        return send_ctrl_msg("ok " + bool_to_enable_string(repeat));
    if(0 == param.find(enable_pcap_token))
        return send_ctrl_msg("ok " + bool_to_enable_string(enable_pcap));
    send_ctrl_msg("fail invalid read parameter");
}

void LTE_fdd_dl_scan_interface::handle_write(std::string msg)
{
    if(0 != msg.find("write "))
        return send_ctrl_msg("fail invalid write command");
    std::string param = msg.substr(6);
    if(0 == param.find(band_token + " "))
        return write_band(param.substr(band_token.length()+1));
    if(0 == param.find(dl_earfcn_list_token + " "))
        return write_dl_earfcn_list(param.substr(dl_earfcn_list_token.length()+1));
    if(0 == param.find(repeat_token + " "))
    {
        repeat = enable_string_to_bool(param.substr(repeat_token.length()+1));
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(enable_pcap_token + " "))
    {
        enable_pcap = enable_string_to_bool(param.substr(enable_pcap_token.length()+1));
        return send_ctrl_msg("ok");
    }
    send_ctrl_msg("fail invalid write parameter");
}

void LTE_fdd_dl_scan_interface::write_band(std::string band_str)
{
    std::lock_guard<std::mutex> lock(dl_earfcn_list_mutex);

    for(uint32 i=0; i<LIBLTE_INTERFACE_BAND_N_ITEMS; i++)
    {
        if(band_str == liblte_interface_band_text[i])
        {
            band = (LIBLTE_INTERFACE_BAND_ENUM)i;
            dl_earfcn_list.clear();
            for(int32 j=0; j<(liblte_interface_last_dl_earfcn[band] -
                              liblte_interface_first_dl_earfcn[band] + 1); j++)
                dl_earfcn_list.push_back(liblte_interface_first_dl_earfcn[band] + j);
            send_ctrl_msg("ok");
            return;
        }
    }
    send_ctrl_msg("fail invalid band");
}

void LTE_fdd_dl_scan_interface::read_dl_earfcn_list()
{
    std::lock_guard<std::mutex> lock(dl_earfcn_list_mutex);
    std::string                 tmp_str;

    for(auto earfcn : dl_earfcn_list)
        tmp_str += std::to_string(earfcn) + ",";
    send_ctrl_msg("ok " + tmp_str.substr(0, tmp_str.length()-1));
}

void LTE_fdd_dl_scan_interface::write_dl_earfcn_list(std::string dl_earfcn_list_str)
{
    std::vector<uint16> tmp_list;
    uint16              tmp_num;
    while(std::string::npos != dl_earfcn_list_str.find(","))
    {
        to_number(dl_earfcn_list_str.substr(0, dl_earfcn_list_str.find(",")), &tmp_num);
        if(tmp_num < liblte_interface_first_dl_earfcn[band] ||
           tmp_num > liblte_interface_last_dl_earfcn[band])
            return send_ctrl_msg("fail invalid dl_earfcn_list");
        tmp_list.push_back(tmp_num);
        dl_earfcn_list_str = dl_earfcn_list_str.substr(dl_earfcn_list_str.find(",")+1);
    }
    to_number(dl_earfcn_list_str, &tmp_num);
    if(tmp_num < liblte_interface_first_dl_earfcn[band] ||
       tmp_num > liblte_interface_last_dl_earfcn[band])
        return send_ctrl_msg("fail invalid dl_earfcn_list");
    tmp_list.push_back(tmp_num);

    std::lock_guard<std::mutex> lock(dl_earfcn_list_mutex);
    dl_earfcn_list.clear();
    dl_earfcn_list = tmp_list;
    send_ctrl_msg("ok");
}

std::string LTE_fdd_dl_scan_interface::bool_to_enable_string(bool value)
{
    if(value)
        return "on";
    return "off";
}

bool LTE_fdd_dl_scan_interface::enable_string_to_bool(std::string enable)
{
    if(enable == "on")
        return true;
    return false;
}

void LTE_fdd_dl_scan_interface::handle_start()
{
    if(flowgraph != NULL)
        return send_ctrl_msg("fail flowgraph already started");

    flowgraph          = new LTE_fdd_dl_scan_flowgraph();
    dl_earfcn_list_idx = 0;
    current_dl_earfcn  = dl_earfcn_list[0];
    if(flowgraph->start(current_dl_earfcn, this))
        return send_ctrl_msg("start fail, likely there is no hardware connected");
    send_ctrl_msg("ok");
}

void LTE_fdd_dl_scan_interface::handle_stop()
{
    if(flowgraph == NULL)
        return send_ctrl_msg("fail not started");

    if(flowgraph->stop())
        return send_ctrl_msg("fail stop issue");
    delete flowgraph;
    flowgraph = NULL;
    send_ctrl_msg("ok");
}

void LTE_fdd_dl_scan_interface::handle_help()
{
    send_ctrl_msg("***System Configuration Parameters***");
    send_ctrl_msg("\tRead parameters using read <param> format");
    send_ctrl_msg("\tSet parameters using write <param> <value> format");
    send_ctrl_msg("\tCommands:");
    send_ctrl_msg("\t\tstart    - Starts scanning the dl_earfcn_list");
    send_ctrl_msg("\t\tstop     - Stops the scan");
    send_ctrl_msg("\t\tshutdown - Stops the scan and exits");
    send_ctrl_msg("\t\thelp     - Prints this screen");
    send_ctrl_msg("\tParameters:");
    send_ctrl_msg("\t\t" + band_token + " = " + liblte_interface_band_text[band]);
    std::string tmp_str  = "\t\t" + dl_earfcn_list_token + " = ";
    std::lock_guard<std::mutex> lock(dl_earfcn_list_mutex);
    for(auto earfcn : dl_earfcn_list)
        tmp_str += std::to_string(earfcn) + ",";
    send_ctrl_msg(tmp_str.substr(0, tmp_str.length()-1));
    send_ctrl_msg("\t\t" + repeat_token + " = " + bool_to_enable_string(repeat));
    send_ctrl_msg("\t\t" + enable_pcap_token + " = " + bool_to_enable_string(enable_pcap));
}

bool LTE_fdd_dl_scan_interface::get_shutdown()
{
    return shutdown;
}

int32 LTE_fdd_dl_scan_interface::switch_to_next_freq()
{
    if(flowgraph == NULL)
        return -1;

    std::lock_guard<std::mutex> lock(dl_earfcn_list_mutex);
    dl_earfcn_list_idx++;
    if(dl_earfcn_list_idx >= dl_earfcn_list.size())
    {
        if(!repeat)
            return -1;
        dl_earfcn_list_idx = 0;
    }
    current_dl_earfcn = dl_earfcn_list[dl_earfcn_list_idx];
    flowgraph->update_center_freq(current_dl_earfcn);
    return 0;
}
