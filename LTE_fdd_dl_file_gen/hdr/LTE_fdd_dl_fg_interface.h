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

    File: LTE_fdd_dl_fg_interface.h

    Description: Contains all the definitions for the LTE FDD DL File Generator
                 interface.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file.

*******************************************************************************/

#ifndef __LTE_FDD_DL_FG_INTERFACE_H__
#define __LTE_FDD_DL_FG_INTERFACE_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_fg_flowgraph.h"
#include "LTE_fdd_dl_fg_samp_buf.h"

#include "libtools_server_socket.h"
#include "EUTRA_RRC_Definitions.h"

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define LTE_FDD_DL_FG_CTRL_PORT 21000

/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_dl_fg_interface
{
public:
    LTE_fdd_dl_fg_interface();
    ~LTE_fdd_dl_fg_interface();
    void start_ctrl_port();
    void stop_ctrl_port();
    void send_ctrl_msg(std::string msg);
    void handle_ctrl_msg(const std::string msg, const int32 sock_fd);
    void handle_ctrl_connect(const int32 sock_fd);
    void handle_ctrl_disconnect(const int32 sock_fd);
    void handle_ctrl_error(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err);
    bool get_shutdown();

private:
    void handle_read(std::string msg);
    void handle_write(std::string msg);
    std::string bandwidth_to_string();
    void write_bandwidth(std::string bw);
    void write_mcc(std::string mcc_value);
    void write_mnc(std::string mnc_value);
    std::string neigh_cell_list_to_string();
    void write_neigh_cell_list(std::string neigh_cell_list);
    void handle_start();
    void handle_stop();
    void handle_help();

    MasterInformationBlock       mib;
    SystemInformationBlockType1  sib1;
    SystemInformationBlockType2  sib2;
    SystemInformationBlockType3  sib3;
    SystemInformationBlockType4  sib4;
    SystemInformationBlockType8  sib8;
    LTE_fdd_dl_fg_flowgraph     *flowgraph;
    LTE_fdd_dl_fg_samp_buf_sptr  samp_buf;
    std::mutex                   ctrl_mutex;
    std::string                  file_name_token;
    std::string                  output_type_token;
    std::string                  bandwidth_token;
    std::string                  freq_band_token;
    std::string                  n_frames_token;
    std::string                  n_ant_token;
    std::string                  n_id_cell_token;
    std::string                  mcc_token;
    std::string                  mnc_token;
    std::string                  cell_id_token;
    std::string                  tracking_area_code_token;
    std::string                  q_rx_lev_min_token;
    std::string                  p0_nominal_pusch_token;
    std::string                  p0_nominal_pucch_token;
    std::string                  q_hyst_token;
    std::string                  neigh_cell_list_token;
    std::string                  search_win_size_token;
    std::string                  percent_load_token;
    std::string                  sib3_present_token;
    std::string                  sib4_present_token;
    std::string                  sib8_present_token;
    std::string                  file_name;
    std::string                  output_type;
    libtools_server_socket      *ctrl_socket;
    uint32                       N_frames;
    uint32                       N_ant;
    uint32                       N_id_cell;
    uint32                       percent_load;
    uint32                       sib3_present;
    uint32                       sib4_present;
    uint32                       sib8_present;
    int32                        ctrl_sock_fd;
    bool                         ctrl_connected;
    bool                         shutdown;
};

#endif // __LTE_FDD_DL_FG_INTERFACE_H__
