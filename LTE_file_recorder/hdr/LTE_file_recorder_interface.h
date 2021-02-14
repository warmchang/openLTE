/*******************************************************************************

    Copyright 2013, 2015, 2021 Ben Wojtowicz

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

    File: LTE_file_recorder_interface.h

    Description: Contains all the definitions for the LTE file recorder
                 interface.

    Revision History
    ----------    -------------    --------------------------------------------
    08/26/2013    Ben Wojtowicz    Created file
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t.
    02/14/2021    Ben Wojtowicz    Massive reformat.

*******************************************************************************/

#ifndef __LTE_FILE_RECORDER_INTERFACE_H__
#define __LTE_FILE_RECORDER_INTERFACE_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_file_recorder_flowgraph.h"
#include "libtools_server_socket.h"
#include <string>
#include <mutex>

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define LTE_FILE_RECORDER_CTRL_PORT 25000

/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_file_recorder_interface
{
public:
    LTE_file_recorder_interface();
    ~LTE_file_recorder_interface();

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
    void write_earfcn(std::string earfcn_str);
    void handle_start();
    void handle_stop();
    void handle_help();

    LTE_file_recorder_flowgraph *flowgraph;
    std::mutex                   ctrl_mutex;
    std::string                  file_name;
    std::string                  earfcn_token;
    std::string                  file_name_token;
    libtools_server_socket      *ctrl_socket;
    int32                        ctrl_sock_fd;
    uint16                       earfcn;
    bool                         ctrl_connected;
    bool                         shutdown;
};

#endif /* __LTE_FILE_RECORDER_INTERFACE_H__ */
