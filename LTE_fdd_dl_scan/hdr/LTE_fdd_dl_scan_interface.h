/*******************************************************************************

    Copyright 2013-2015, 2021 Ben Wojtowicz
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

    File: LTE_fdd_dl_scan_interface.h

    Description: Contains all the definitions for the LTE FDD DL Scanner
                 interface.

    Revision History
    ----------    -------------    --------------------------------------------
    02/26/2013    Ben Wojtowicz    Created file
    07/21/2013    Ben Wojtowicz    Added support for decoding SIBs.
    06/15/2014    Ben Wojtowicz    Added PCAP support.
    09/19/2014    Andrew Murphy    Added SIB13 printing.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t.
    02/14/2021    Ben Wojtowicz    Massive reformat and using the new RRC
                                   library.

*******************************************************************************/

#ifndef __LTE_FDD_DL_SCAN_INTERFACE_H__
#define __LTE_FDD_DL_SCAN_INTERFACE_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_scan_flowgraph.h"
#include "liblte_interface.h"
#include "liblte_common.h"
#include "EUTRA_RRC_Definitions.h"
#include "libtools_server_socket.h"
#include <string>

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define LTE_FDD_DL_SCAN_CTRL_PORT 20000

/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/

typedef enum{
    LTE_FDD_DL_SCAN_STATUS_OK = 0,
    LTE_FDD_DL_SCAN_STATUS_FAIL,
}LTE_FDD_DL_SCAN_STATUS_ENUM;

/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_dl_scan_interface
{
public:
    LTE_fdd_dl_scan_interface();
    ~LTE_fdd_dl_scan_interface();

    void start_ctrl_port();
    void stop_ctrl_port();
    void send_ctrl_msg(std::string msg);
    void send_channel_found_begin_msg(float freq_offset, uint32 N_id_cell, const MasterInformationBlock &mib, uint32 sfn, uint8 N_ant);
    void send_sib1_msg(float freq_offset, uint32 N_id_cell, const SystemInformationBlockType1 &sib1, uint32 sfn);
    void send_sib_msg(float freq_offset, uint32 N_id_cell, const SystemInformation_r8_IEs &sib, uint32 sfn);
    void send_channel_found_end_msg(float freq_offset, uint32 N_id_cell);
    void send_channel_not_found_msg();
    void open_pcap_fd();
    void send_pcap_msg(uint32 rnti, uint32 current_tti, LIBLTE_BIT_MSG_STRUCT &msg);
    void handle_ctrl_msg(const std::string msg, const int32 sock_fd);
    void handle_ctrl_connect(const int32 sock_fd);
    void handle_ctrl_disconnect(const int32 sock_fd);
    void handle_ctrl_error(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err);
    bool get_shutdown();
    int32 switch_to_next_freq();

private:
    void handle_read(std::string msg);
    void handle_write(std::string msg);
    void write_band(std::string band_str);
    void read_dl_earfcn_list();
    void write_dl_earfcn_list(std::string dl_earfcn_list_str);
    std::string bool_to_enable_string(bool value);
    bool enable_string_to_bool(std::string enable);
    void handle_start();
    void handle_stop();
    void handle_help();

    LTE_fdd_dl_scan_flowgraph  *flowgraph;
    std::mutex                  dl_earfcn_list_mutex;
    std::mutex                  ctrl_mutex;
    std::vector<uint16>         dl_earfcn_list;
    std::string                 band_token;
    std::string                 dl_earfcn_list_token;
    std::string                 repeat_token;
    std::string                 enable_pcap_token;
    FILE                       *pcap_fd;
    libtools_server_socket     *ctrl_socket;
    LIBLTE_INTERFACE_BAND_ENUM  band;
    int32                       ctrl_sock_fd;
    uint16                      current_dl_earfcn;
    uint16                      dl_earfcn_list_idx;
    bool                        ctrl_connected;
    bool                        repeat;
    bool                        enable_pcap;
    bool                        shutdown;
};

#endif /* __LTE_FDD_DL_SCAN_INTERFACE_H__ */
