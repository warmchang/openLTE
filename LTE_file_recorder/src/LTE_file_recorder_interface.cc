/*******************************************************************************

    Copyright 2013, 2015, 2017, 2021 Ben Wojtowicz

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

    File: LTE_file_recorder_interface.cc

    Description: Contains all the implementations for the LTE file recorder
                 interface.

    Revision History
    ----------    -------------    --------------------------------------------
    08/26/2013    Ben Wojtowicz    Created file
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t.
    07/29/2017    Ben Wojtowicz    Using the latest tools library.
    02/14/2021    Ben Wojtowicz    Massive reformat.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_file_recorder_interface.h"
#include "liblte_interface.h"
#include "libtools_helpers.h"

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

LTE_file_recorder_interface::LTE_file_recorder_interface() :
    flowgraph{NULL}, file_name{"/tmp/lte_iq_file.bin"}, earfcn_token{"earfcn"},
    file_name_token{"file_name"}, ctrl_socket{NULL},
    earfcn{liblte_interface_first_dl_earfcn[0]}, ctrl_connected{false}, shutdown{false}
{
}
LTE_file_recorder_interface::~LTE_file_recorder_interface()
{
    stop_ctrl_port();

    if(flowgraph != NULL)
        delete flowgraph;
}

void LTE_file_recorder_interface::start_ctrl_port()
{
    std::lock_guard<std::mutex>       lock(ctrl_mutex);
    LIBTOOLS_SERVER_SOCKET_ERROR_ENUM error;

    if(NULL != ctrl_socket)
        return;

    libtools_server_socket_receive_callback receive_cb(
        &libtools_server_socket_receive_callback::wrapper<LTE_file_recorder_interface, &LTE_file_recorder_interface::handle_ctrl_msg>,
        this);
    libtools_server_socket_connect_disconnect_callback connect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_file_recorder_interface, &LTE_file_recorder_interface::handle_ctrl_connect>,
        this);
    libtools_server_socket_connect_disconnect_callback disconnect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_file_recorder_interface, &LTE_file_recorder_interface::handle_ctrl_disconnect>,
        this);
    libtools_server_socket_error_callback error_cb(
        &libtools_server_socket_error_callback::wrapper<LTE_file_recorder_interface, &LTE_file_recorder_interface::handle_ctrl_error>,
        this);
    ctrl_socket = new libtools_server_socket(LTE_FILE_RECORDER_CTRL_PORT, receive_cb,
                                             connect_cb, disconnect_cb, error_cb, error);
    if(LIBTOOLS_SERVER_SOCKET_ERROR_NONE == error)
        return;
    printf("ERROR: Couldn't open ctrl_socket %u\n", error);
    ctrl_socket = NULL;
}

void LTE_file_recorder_interface::stop_ctrl_port()
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(NULL == ctrl_socket)
        return;

    delete ctrl_socket;
    ctrl_socket = NULL;
}

void LTE_file_recorder_interface::send_ctrl_msg(std::string msg)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(!ctrl_connected)
        return;

    ctrl_socket->send(msg + "\n", ctrl_sock_fd);
}

void LTE_file_recorder_interface::handle_ctrl_msg(const std::string msg,
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

void LTE_file_recorder_interface::handle_ctrl_connect(const int32 sock_fd)
{
    ctrl_mutex.lock();
    ctrl_connected = true;
    ctrl_sock_fd   = sock_fd;
    ctrl_mutex.unlock();

    send_ctrl_msg("*** LTE File Recorder ***");
    send_ctrl_msg("Type help to see a list of commands");
}

void LTE_file_recorder_interface::handle_ctrl_disconnect(const int32 sock_fd)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    ctrl_connected = false;
}

void LTE_file_recorder_interface::handle_ctrl_error(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err)
{
    printf("ERROR: ctrl_socket error %u\n", err);
    assert(0);
}

void LTE_file_recorder_interface::handle_read(std::string msg)
{
    if(0 != msg.find("read "))
        return send_ctrl_msg("fail invalid read command");
    std::string param = msg.substr(5);
    if(0 == param.find(earfcn_token))
        return send_ctrl_msg("ok " + std::to_string(earfcn));
    if(0 == param.find(file_name_token))
        return send_ctrl_msg("ok " + file_name);
    send_ctrl_msg("fail invalid read parameter");
}

void LTE_file_recorder_interface::handle_write(std::string msg)
{
    if(0 != msg.find("write "))
        return send_ctrl_msg("fail invalid write command");
    std::string param = msg.substr(6);
    if(0 == param.find(earfcn_token))
        return write_earfcn(param.substr(earfcn_token.length()+1));
    if(0 == param.find(file_name_token))
    {
        file_name = param.substr(file_name_token.length()+1);
        return send_ctrl_msg("ok");
    }
    send_ctrl_msg("fail invalid write parameter");
}

void LTE_file_recorder_interface::write_earfcn(std::string earfcn_str)
{
    uint16 tmp_earfcn = LIBLTE_INTERFACE_DL_EARFCN_INVALID;

    to_number(earfcn_str, &tmp_earfcn);

    if(0 == liblte_interface_dl_earfcn_to_frequency(tmp_earfcn) &&
       0 == liblte_interface_ul_earfcn_to_frequency(tmp_earfcn))
        return send_ctrl_msg("fail invalid earfcn");
    earfcn = tmp_earfcn;
    send_ctrl_msg("ok");
}

void LTE_file_recorder_interface::handle_start()
{
    if(flowgraph != NULL)
        return send_ctrl_msg("fail flowgraph already started");

    flowgraph = new LTE_file_recorder_flowgraph();
    if(flowgraph->start(earfcn, file_name))
        return send_ctrl_msg("start fail, likely there is no hardware connected");
    send_ctrl_msg("ok");
}

void LTE_file_recorder_interface::handle_stop()
{
    if(flowgraph == NULL)
        return send_ctrl_msg("fail not started");

    if(flowgraph->stop())
        return send_ctrl_msg("fail stop issue");
    delete flowgraph;
    flowgraph = NULL;
    send_ctrl_msg("ok");
}

void LTE_file_recorder_interface::handle_help()
{
    send_ctrl_msg("***System Configuration Parameters***");
    send_ctrl_msg("\tRead parameters using read <param> format");
    send_ctrl_msg("\tSet parameters using write <param> <value> format");
    send_ctrl_msg("\tCommands:");
    send_ctrl_msg("\t\tstart    - Starts recording the specified earfcn");
    send_ctrl_msg("\t\tstop     - Stops the recording");
    send_ctrl_msg("\t\tshutdown - Stops the recording and exits");
    send_ctrl_msg("\t\thelp     - Prints this screen");
    send_ctrl_msg("\tParameters:");
    send_ctrl_msg("\t\t" + earfcn_token + " = " + std::to_string(earfcn));
    send_ctrl_msg("\t\t" + file_name_token + " = " + file_name);
}

bool LTE_file_recorder_interface::get_shutdown()
{
    return shutdown;
}
