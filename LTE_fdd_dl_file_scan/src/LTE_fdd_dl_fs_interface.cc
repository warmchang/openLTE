/*******************************************************************************

    Copyright 2021 Ben Wojtowicz

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

    File: LTE_fdd_dl_fs_interface.cc

    Description: Contains all the implementations for the LTE FDD DL File
                 Scanner interface.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_fs_interface.h"

#include "assert.h"
#include "arpa/inet.h"

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

LTE_fdd_dl_fs_interface::LTE_fdd_dl_fs_interface() :
    flowgraph{NULL}, file_name_token{"file_name"}, input_type_token{"input_type"},
    samp_rate_token("samp_rate"), enable_pcap_token{"enable_pcap"},
    file_name{"/tmp/LTE_fdd_dl_fs_samps.bin"}, input_type{"gr_complex"}, pcap_fd{NULL},
    samp_rate{LIBLTE_PHY_FS_30_72MHZ}, ctrl_socket{NULL}, ctrl_connected{false},
    shutdown{false}, enable_pcap{false}
{
    open_pcap_fd();

    start_ctrl_port();
}

LTE_fdd_dl_fs_interface::~LTE_fdd_dl_fs_interface()
{
    stop_ctrl_port();

    if(flowgraph != NULL)
        delete flowgraph;

    fclose(pcap_fd);
}

void LTE_fdd_dl_fs_interface::start_ctrl_port()
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(NULL != ctrl_socket)
        return;

    libtools_server_socket_receive_callback receive_cb(
        &libtools_server_socket_receive_callback::wrapper<LTE_fdd_dl_fs_interface, &LTE_fdd_dl_fs_interface::handle_ctrl_msg>,
        this);
    libtools_server_socket_connect_disconnect_callback connect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_fdd_dl_fs_interface, &LTE_fdd_dl_fs_interface::handle_ctrl_connect>,
        this);
    libtools_server_socket_connect_disconnect_callback disconnect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_fdd_dl_fs_interface, &LTE_fdd_dl_fs_interface::handle_ctrl_disconnect>,
        this);
    libtools_server_socket_error_callback error_cb(
        &libtools_server_socket_error_callback::wrapper<LTE_fdd_dl_fs_interface, &LTE_fdd_dl_fs_interface::handle_ctrl_error>,
        this);

    LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err;
    ctrl_socket = new libtools_server_socket(LTE_FDD_DL_FS_CTRL_PORT, receive_cb, connect_cb,
                                             disconnect_cb, error_cb, err);
    if(err == LIBTOOLS_SERVER_SOCKET_ERROR_NONE)
        return;
    printf("ERROR: Couldn't open ctrl_socket %u\n", err);
    ctrl_socket = NULL;
}

void LTE_fdd_dl_fs_interface::stop_ctrl_port()
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(NULL == ctrl_socket)
        return;

    delete ctrl_socket;
    ctrl_socket = NULL;
}

void LTE_fdd_dl_fs_interface::send_ctrl_msg(std::string msg)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(!ctrl_connected)
        return;

    ctrl_socket->send(msg + "\n", ctrl_sock_fd);
}

void LTE_fdd_dl_fs_interface::send_channel_found_begin_msg(float freq_offset,
                                                           uint32 N_id_cell,
                                                           const MasterInformationBlock &mib,
                                                           uint32 sfn,
                                                           uint8 N_ant)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(!ctrl_connected)
        return;

    std::string msg = "info channel_found_begin freq_offset=";
    msg += std::to_string(freq_offset) + " PCI=" + std::to_string(N_id_cell) + " sfn=";
    msg += std::to_string(sfn) + " N_ant=" + std::to_string(N_ant) + " ";
    msg += mib.ToStringNoNewLines() + "\n";
    ctrl_socket->send(msg, ctrl_sock_fd);
}

void LTE_fdd_dl_fs_interface::send_sib1_msg(float freq_offset,
                                            uint32 N_id_cell,
                                            const SystemInformationBlockType1 &sib1,
                                            uint32 sfn)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(!ctrl_connected)
        return;

    std::string msg = "info sib1_decoded freq_offset=" + std::to_string(freq_offset) + " ";
    msg += "PCI=" + std::to_string(N_id_cell) + " sfn=" + std::to_string(sfn) + " ";
    msg += sib1.ToStringNoNewLines() + "\n";
    ctrl_socket->send(msg, ctrl_sock_fd);
}

void LTE_fdd_dl_fs_interface::send_sib_msg(float freq_offset,
                                           uint32 N_id_cell,
                                           const SystemInformation_r8_IEs &sib,
                                           uint32 sfn)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(!ctrl_connected)
        return;

    std::string msg = "info sib_decoded freq_offset=" + std::to_string(freq_offset) + " ";
    msg += "PCI=" + std::to_string(N_id_cell) + " sfn=" + std::to_string(sfn) + " ";
    msg += sib.ToStringNoNewLines() + "\n";
    ctrl_socket->send(msg, ctrl_sock_fd);
}

void LTE_fdd_dl_fs_interface::send_channel_found_end_msg(float freq_offset,
                                                         uint32 N_id_cell)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(!ctrl_connected)
        return;

    std::string msg = "info channel_found_end freq_offset=" + std::to_string(freq_offset) + " ";
    msg += "PCI=" + std::to_string(N_id_cell) + "\n";
    ctrl_socket->send(msg, ctrl_sock_fd);
}

void LTE_fdd_dl_fs_interface::send_channel_not_found_msg()
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(!ctrl_connected)
        return;

    ctrl_socket->send("info channel_not_found\n", ctrl_sock_fd);
}

void LTE_fdd_dl_fs_interface::open_pcap_fd()
{
    uint32 magic_number  = 0xa1b2c3d4;
    uint32 timezone      = 0;
    uint32 sigfigs       = 0;
    uint32 snap_len      = (LIBLTE_MAX_MSG_SIZE/4);
    uint32 dlt           = 147;
    uint16 major_version = 2;
    uint16 minor_version = 4;

    pcap_fd = fopen("/tmp/LTE_fdd_dl_file_scan.pcap", "w");

    fwrite(&magic_number,  sizeof(magic_number),  1, pcap_fd);
    fwrite(&major_version, sizeof(major_version), 1, pcap_fd);
    fwrite(&minor_version, sizeof(minor_version), 1, pcap_fd);
    fwrite(&timezone,      sizeof(timezone),      1, pcap_fd);
    fwrite(&sigfigs,       sizeof(sigfigs),       1, pcap_fd);
    fwrite(&snap_len,      sizeof(snap_len),      1, pcap_fd);
    fwrite(&dlt,           sizeof(dlt),           1, pcap_fd);
}

void LTE_fdd_dl_fs_interface::send_pcap_msg(uint32                 rnti,
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

void LTE_fdd_dl_fs_interface::handle_ctrl_msg(const std::string msg,
                                              const int32       sock_fd)
{
    if(0 == msg.find("shutdown"))
    {
        send_ctrl_msg("ok");
        shutdown = true;
        return;
    }
    if(0 == msg.find("start"))
        return handle_start();
    if(0 == msg.find("stop"))
        return handle_stop();
    if(0 == msg.find("read"))
        return handle_read(msg);
    if(0 == msg.find("write"))
        return handle_write(msg);
    if(0 == msg.find("help"))
        return handle_help();
    send_ctrl_msg("fail invalid command");
}

void LTE_fdd_dl_fs_interface::handle_ctrl_connect(const int32 sock_fd)
{
    ctrl_mutex.lock();
    ctrl_connected = true;
    ctrl_sock_fd   = sock_fd;
    ctrl_mutex.unlock();

    send_ctrl_msg("*** LTE FDD DL FILE SCAN ***");
    send_ctrl_msg("Type help to see a list of commands");
}

void LTE_fdd_dl_fs_interface::handle_ctrl_disconnect(const int32 sock_fd)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    ctrl_connected = false;
}

void LTE_fdd_dl_fs_interface::handle_ctrl_error(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err)
{
    printf("ERROR: ctrl_socket error %u\n", err);
    assert(0);
}

void LTE_fdd_dl_fs_interface::handle_read(std::string msg)
{
    if(0 != msg.find("read "))
        return send_ctrl_msg("fail invalid read command");
    std::string param = msg.substr(5);
    if(0 == param.find(file_name_token))
        return send_ctrl_msg("ok " + file_name);
    if(0 == param.find(input_type_token))
        return send_ctrl_msg("ok " + input_type);
    if(0 == param.find(samp_rate_token))
        return send_ctrl_msg("ok " + samp_rate_to_string());
    if(0 == param.find(enable_pcap_token))
        return send_ctrl_msg("ok " + bool_to_enable_string(enable_pcap));
    send_ctrl_msg("fail invalid read parameter");
}

void LTE_fdd_dl_fs_interface::handle_write(std::string msg)
{
    if(0 != msg.find("write "))
        return send_ctrl_msg("fail invalid write command");
    std::string param = msg.substr(6);
    if(0 == param.find(file_name_token + " "))
    {
        file_name = param.substr(file_name_token.length()+1);
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(input_type_token + " "))
    {
        if(0 == param.substr(input_type_token.length()+1).find("int8"))
        {
            input_type = "int8";
            return send_ctrl_msg("ok");
        }
        if(0 == param.substr(input_type_token.length()+1).find("gr_complex"))
        {
            input_type = "gr_complex";
            return send_ctrl_msg("ok");
        }
        return send_ctrl_msg("fail invalid input_type");
    }
    if(0 == param.find(samp_rate_token + " "))
        return write_samp_rate(param.substr(samp_rate_token.length()+1));
    if(0 == param.find(enable_pcap_token + " "))
    {
        enable_pcap = enable_string_to_bool(param.substr(enable_pcap_token.length()+1));
        return send_ctrl_msg("ok");
    }
    send_ctrl_msg("fail invalid write parameter");
}

std::string LTE_fdd_dl_fs_interface::samp_rate_to_string()
{
    if(samp_rate == LIBLTE_PHY_FS_30_72MHZ)
        return "30.72";
    if(samp_rate == LIBLTE_PHY_FS_15_36MHZ)
        return "15.36";
    if(samp_rate == LIBLTE_PHY_FS_7_68MHZ)
        return "7.68";
    if(samp_rate == LIBLTE_PHY_FS_3_84MHZ)
        return "3.84";
    if(samp_rate == LIBLTE_PHY_FS_1_92MHZ)
        return "1.92";
    return "";
}

void LTE_fdd_dl_fs_interface::write_samp_rate(std::string sr)
{
    if(0 == sr.find("30.72"))
    {
        samp_rate = LIBLTE_PHY_FS_30_72MHZ;
        return send_ctrl_msg("ok");
    }
    if(0 == sr.find("15.36"))
    {
        samp_rate = LIBLTE_PHY_FS_15_36MHZ;
        return send_ctrl_msg("ok");
    }
    if(0 == sr.find("7.68"))
    {
        samp_rate = LIBLTE_PHY_FS_7_68MHZ;
        return send_ctrl_msg("ok");
    }
    if(0 == sr.find("3.84"))
    {
        samp_rate = LIBLTE_PHY_FS_3_84MHZ;
        return send_ctrl_msg("ok");
    }
    if(0 == sr.find("1.92"))
    {
        samp_rate = LIBLTE_PHY_FS_1_92MHZ;
        return send_ctrl_msg("ok");
    }
    send_ctrl_msg("fail invalid samp_rate");
}

std::string LTE_fdd_dl_fs_interface::bool_to_enable_string(bool value)
{
    if(value)
        return "on";
    return "off";
}

bool LTE_fdd_dl_fs_interface::enable_string_to_bool(std::string enable)
{
    if(enable == "on")
        return true;
    return false;
}

void LTE_fdd_dl_fs_interface::handle_start()
{
    if(flowgraph != NULL)
        return send_ctrl_msg("fail already started");

    if(scan_block.get() != NULL)
        scan_block.reset();
    size_t samp_size = sizeof(int8);
    if(input_type == "gr_complex")
        samp_size = sizeof(gr_complex);
    flowgraph = new LTE_fdd_dl_fs_flowgraph();
    liblte_fdd_dl_scan_block_is_started_callback is_cb(
        &liblte_fdd_dl_scan_block_is_started_callback::wrapper<LTE_fdd_dl_fs_flowgraph, &LTE_fdd_dl_fs_flowgraph::is_started>,
        flowgraph);
    liblte_fdd_dl_scan_block_send_pcap_callback sp_cb(
        &liblte_fdd_dl_scan_block_send_pcap_callback::wrapper<LTE_fdd_dl_fs_interface, &LTE_fdd_dl_fs_interface::send_pcap_msg>,
        this);
    liblte_fdd_dl_scan_block_send_channel_found_begin_callback scfb_cb(
        &liblte_fdd_dl_scan_block_send_channel_found_begin_callback::wrapper<LTE_fdd_dl_fs_interface, &LTE_fdd_dl_fs_interface::send_channel_found_begin_msg>,
        this);
    liblte_fdd_dl_scan_block_send_sib1_callback ss1_cb(
        &liblte_fdd_dl_scan_block_send_sib1_callback::wrapper<LTE_fdd_dl_fs_interface, &LTE_fdd_dl_fs_interface::send_sib1_msg>,
        this);
    liblte_fdd_dl_scan_block_send_sib_callback ss_cb(
        &liblte_fdd_dl_scan_block_send_sib_callback::wrapper<LTE_fdd_dl_fs_interface, &LTE_fdd_dl_fs_interface::send_sib_msg>,
        this);
    liblte_fdd_dl_scan_block_send_channel_found_end_callback scfe_cb(
        &liblte_fdd_dl_scan_block_send_channel_found_end_callback::wrapper<LTE_fdd_dl_fs_interface, &LTE_fdd_dl_fs_interface::send_channel_found_end_msg>,
        this);
    liblte_fdd_dl_scan_block_send_channel_not_found_callback scnf_cb(
        &liblte_fdd_dl_scan_block_send_channel_not_found_callback::wrapper<LTE_fdd_dl_fs_interface, &LTE_fdd_dl_fs_interface::send_channel_not_found_msg>,
        this);
    scan_block = liblte_fdd_dl_scan_block_make(is_cb, sp_cb, scfb_cb, ss1_cb, ss_cb, scfe_cb,
                                               scnf_cb, samp_size, 20, samp_rate);
    if(flowgraph->start(file_name, scan_block, samp_size))
        return send_ctrl_msg("fail start issue");
    send_ctrl_msg("ok");
}

void LTE_fdd_dl_fs_interface::handle_stop()
{
    if(flowgraph == NULL)
        return send_ctrl_msg("fail not started");

    if(flowgraph->stop())
        return send_ctrl_msg("fail stop issue");
    delete flowgraph;
    flowgraph = NULL;
    scan_block.reset();
    send_ctrl_msg("ok");
}

void LTE_fdd_dl_fs_interface::handle_help()
{
    send_ctrl_msg("*** LTE FDD DL FILE SCAN HELP ***");
    send_ctrl_msg("Commands:");
    send_ctrl_msg("\tstart    - Starts scanning the input file with the current parameters");
    send_ctrl_msg("\tstop     - Stops scanning the input file");
    send_ctrl_msg("\tshutdown - Shuts down the entire application");
    send_ctrl_msg("\thelp     - Prints this screen");
    send_ctrl_msg("\tread     - Reads the specified parameter (read <param>)");
    send_ctrl_msg("\twrite    - Writes the specified parameter (write <param> <value>)");
    send_ctrl_msg("Parameters:");
    send_ctrl_msg("\t\t" + file_name_token + " = " + file_name);
    send_ctrl_msg("\t\t" + input_type_token + " = " + input_type);
    send_ctrl_msg("\t\t" + samp_rate_token + " = " + samp_rate_to_string());
    send_ctrl_msg("\t\t" + enable_pcap_token + " = " + bool_to_enable_string(enable_pcap));
}

bool LTE_fdd_dl_fs_interface::get_shutdown()
{
    return shutdown;
}
