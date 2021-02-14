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

    File: LTE_fdd_dl_fs_interface.h

    Description: Contains all the definitions for the LTE FDD DL File Scanner
                 interface.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file.

*******************************************************************************/

#ifndef __LTE_FDD_DL_FS_INTERFACE_H__
#define __LTE_FDD_DL_FS_INTERFACE_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_fs_flowgraph.h"
#include "liblte_fdd_dl_scan_block.h"

#include "libtools_server_socket.h"
#include "liblte_phy.h"

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define LTE_FDD_DL_FS_CTRL_PORT 22000

/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_dl_fs_interface
{
public:
    LTE_fdd_dl_fs_interface();
    ~LTE_fdd_dl_fs_interface();
    void start_ctrl_port();
    void stop_ctrl_port();
    void send_ctrl_msg(std::string msg);
    void send_channel_found_begin_msg(float freq_offset, uint32 N_id_cell, const MasterInformationBlock &mib, uint32 sfn, uint8 N_ant);
    void send_sib1_msg(float freq_offset, uint32 N_id_cell, const SystemInformationBlockType1 &sib1, uint32 sfn);
    void send_sib_msg(float freq_offset, uint32 N_id_cell, const SystemInformation_r8_IEs &sib, uint32 sfn);
    void send_channel_found_end_msg(float freq_ofsfet, uint32 N_id_cell);
    void send_channel_not_found_msg();
    void open_pcap_fd();
    void send_pcap_msg(uint32 rnti, uint32 current_tti, LIBLTE_BIT_MSG_STRUCT &msg);
    void handle_ctrl_msg(const std::string msg, const int32 sock_fd);
    void handle_ctrl_connect(const int32 sock_fd);
    void handle_ctrl_disconnect(const int32 sock_fd);
    void handle_ctrl_error(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err);
    bool get_shutdown();

private:
    void handle_read(std::string msg);
    void handle_write(std::string msg);
    std::string samp_rate_to_string();
    void write_samp_rate(std::string sr);
    std::string bool_to_enable_string(bool value);
    bool enable_string_to_bool(std::string enable);
    void handle_start();
    void handle_stop();
    void handle_help();

    LTE_fdd_dl_fs_flowgraph      *flowgraph;
    liblte_fdd_dl_scan_block_sptr scan_block;
    std::mutex                    ctrl_mutex;
    std::string                   file_name_token;
    std::string                   input_type_token;
    std::string                   samp_rate_token;
    std::string                   enable_pcap_token;
    std::string                   file_name;
    std::string                   input_type;
    FILE                         *pcap_fd;
    LIBLTE_PHY_FS_ENUM            samp_rate;
    libtools_server_socket       *ctrl_socket;
    int32                         ctrl_sock_fd;
    bool                          ctrl_connected;
    bool                          shutdown;
    bool                          enable_pcap;
};

#endif // __LTE_FDD_DL_FS_INTERFACE_H__
