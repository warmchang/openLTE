/*******************************************************************************

    Copyright 2013, 2021 Ben Wojtowicz

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

    File: libtools_server_socket.h

    Description: Contains all the definitions for the server socket
                 abstraction.

    Revision History
    ----------    -------------    --------------------------------------------
    02/26/2013    Ben Wojtowicz    Created file
    02/14/2021    Ben Wojtowicz    Migrated from libtools_socket_wrap.h

*******************************************************************************/

#ifndef __LIBTOOLS_SERVER_SOCKET_H__
#define __LIBTOOLS_SERVER_SOCKET_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "typedefs.h"
#include <mutex>
#include <thread>
#include <map>

/*******************************************************************************
                              DEFINES
*******************************************************************************/


/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/

typedef enum{
    LIBTOOLS_SERVER_SOCKET_ERROR_NONE = 0,
    LIBTOOLS_SERVER_SOCKET_ERROR_INVALID_INPUTS,
    LIBTOOLS_SERVER_SOCKET_ERROR_SOCKET,
    LIBTOOLS_SERVER_SOCKET_ERROR_PTHREAD,
    LIBTOOLS_SERVER_SOCKET_ERROR_WRITE_FAIL,
    LIBTOOLS_SERVER_SOCKET_ERROR_N_ITEMS,
}LIBTOOLS_SERVER_SOCKET_ERROR_ENUM;
static const char libtools_server_socket_error_text[LIBTOOLS_SERVER_SOCKET_ERROR_N_ITEMS][20] = {"None",
                                                                                                 "Invalid Inputs",
                                                                                                 "Socket",
                                                                                                 "PThread",
                                                                                                 "Write Fail"};
/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class libtools_server_socket_receive_callback
{
public:
    template<class C, void (C::*Func)(const std::string, const int32)>
        static void wrapper(void *o, const std::string msg, const int32 sock_fd) {return (static_cast<C*>(o)->*Func)(msg, sock_fd);}
    typedef void (*FuncType)(void*, const std::string, const int32);
    libtools_server_socket_receive_callback(FuncType f, void *o) : func{f}, obj{o} {};
    void operator()(const std::string msg, const int32 sock_fd) { return (*func)(obj, msg, sock_fd); };
private:
    FuncType  func;
    void     *obj;
};

class libtools_server_socket_connect_disconnect_callback
{
public:
    template<class C, void (C::*Func)(const int32)>
        static void wrapper(void *o, const int32 sock_fd) {return (static_cast<C*>(o)->*Func)(sock_fd);}
    typedef void (*FuncType)(void*, int32);
    libtools_server_socket_connect_disconnect_callback(FuncType f, void *o) : func{f}, obj{o} {};
    void operator()(const int32 sock_fd) { return (*func)(obj, sock_fd); };
private:
    FuncType  func;
    void     *obj;
};

class libtools_server_socket_error_callback
{
public:
    template<class C, void (C::*Func)(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM)>
        static void wrapper(void *o, const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM error) {return (static_cast<C*>(o)->*Func)(error);}
    typedef void (*FuncType)(void*, LIBTOOLS_SERVER_SOCKET_ERROR_ENUM);
    libtools_server_socket_error_callback(FuncType f, void *o) : func{f}, obj{o} {};
    void operator()(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM error) { return (*func)(obj, error); };
private:
    FuncType  func;
    void     *obj;
};

class libtools_server_socket
{
public:
    libtools_server_socket(const uint16                                              _port,
                           const libtools_server_socket_receive_callback            &_receive_cb,
                           const libtools_server_socket_connect_disconnect_callback &_connect_cb,
                           const libtools_server_socket_connect_disconnect_callback &_disconnect_cb,
                           const libtools_server_socket_error_callback              &_error_cb,
                           LIBTOOLS_SERVER_SOCKET_ERROR_ENUM                        &error);
    ~libtools_server_socket();

    // Send
    LIBTOOLS_SERVER_SOCKET_ERROR_ENUM send(const std::string msg, const int32 sock_fd);
private:
    // Receive
    static void rx_thread(libtools_server_socket *server_socket);

    // Variables
    libtools_server_socket_receive_callback             receive_cb;
    libtools_server_socket_connect_disconnect_callback  connect_cb;
    libtools_server_socket_connect_disconnect_callback  disconnect_cb;
    libtools_server_socket_error_callback               error_cb;
    std::thread                                        *socket_thread;
    std::mutex                                          socket_mutex;
    std::map<int32, std::mutex*>                        client_mutex;
    int32                                               sock;
    uint16                                              port;
};

#endif /* __LIBTOOLS_SERVER_SOCKET_H__ */
