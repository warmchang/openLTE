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

    File: libtools_server_socket.cc

    Description: Contains all the implementations for the server socket
                 abstraction.

    Revision History
    ----------    -------------    --------------------------------------------
    02/26/2013    Ben Wojtowicz    Created file
    02/14/2021    Ben Wojtowicz    Migrated from libtools_socket_wrap.cc

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "libtools_server_socket.h"
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

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

// Constructor/Destructor
libtools_server_socket::libtools_server_socket(const uint16                                              _port,
                                               const libtools_server_socket_receive_callback            &_receive_cb,
                                               const libtools_server_socket_connect_disconnect_callback &_connect_cb,
                                               const libtools_server_socket_connect_disconnect_callback &_disconnect_cb,
                                               const libtools_server_socket_error_callback              &_error_cb,
                                               LIBTOOLS_SERVER_SOCKET_ERROR_ENUM                        &error) :
    receive_cb{_receive_cb}, connect_cb{_connect_cb}, disconnect_cb{_disconnect_cb},
    error_cb{_error_cb}, port{_port}
{
    std::lock_guard<std::mutex> lock(socket_mutex);

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock < 0)
    {
        error = LIBTOOLS_SERVER_SOCKET_ERROR_SOCKET;
        return;
    }

    struct linger linger;
    linger.l_onoff  = 1;
    linger.l_linger = 0;
    if(0 != setsockopt(sock, SOL_SOCKET, SO_LINGER, &linger, sizeof(linger)))
    {
        error = LIBTOOLS_SERVER_SOCKET_ERROR_SOCKET;
        return;
    }

    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family      = AF_INET;
    s_addr.sin_addr.s_addr = INADDR_ANY;
    s_addr.sin_port        = htons(port);
    if(0 != bind(sock, (struct sockaddr *)&s_addr, sizeof(s_addr)))
    {
        error = LIBTOOLS_SERVER_SOCKET_ERROR_SOCKET;
        return;
    }

    // Create read thread
    socket_thread = new std::thread(rx_thread, this);
    error = LIBTOOLS_SERVER_SOCKET_ERROR_NONE;
}
libtools_server_socket::~libtools_server_socket()
{
    std::lock_guard<std::mutex> lock(socket_mutex);
    close(sock);
    sleep(1);
    socket_thread->join();
    delete socket_thread;
}
LIBTOOLS_SERVER_SOCKET_ERROR_ENUM libtools_server_socket::send(const std::string msg,
                                                               const int32       sock_fd)
{
    std::lock_guard<std::mutex> lock(*client_mutex[sock_fd]);
    if((ssize_t)msg.size() != write(sock_fd, msg.c_str(), msg.size()))
        return LIBTOOLS_SERVER_SOCKET_ERROR_WRITE_FAIL;
    return LIBTOOLS_SERVER_SOCKET_ERROR_NONE;
}
void libtools_server_socket::rx_thread(libtools_server_socket *server_socket)
{
    server_socket->socket_mutex.lock();
    if(0 != listen(server_socket->sock, 1))
    {
        server_socket->error_cb(LIBTOOLS_SERVER_SOCKET_ERROR_SOCKET);
        server_socket->socket_mutex.unlock();
        return;
    }
    server_socket->socket_mutex.unlock();

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(server_socket->sock, &fds);
    int32 fd_max = server_socket->sock;

    while(1)
    {
        struct timeval select_timeout;
        select_timeout.tv_sec  = 0;
        select_timeout.tv_usec = 500000;
        fd_set tmp_fds         = fds;
        if(select(fd_max+1, &tmp_fds, NULL, NULL, &select_timeout) == -1)
            continue;

        for(int32 i=0; i<=fd_max; i++)
        {
            if(FD_ISSET(i, &tmp_fds))
            {
                if(i == server_socket->sock)
                {
                    std::lock_guard<std::mutex> lock(server_socket->socket_mutex);
                    struct sockaddr_in c_addr;
                    socklen_t c_addr_len = sizeof(c_addr);
                    int32 sock_fd = accept(server_socket->sock, (struct sockaddr *)&c_addr,
                                           &c_addr_len);
                    if(sock_fd < 0)
                    {
                        server_socket->error_cb(LIBTOOLS_SERVER_SOCKET_ERROR_SOCKET);
                        break;
                    }
                    FD_SET(sock_fd, &fds);
                    if(sock_fd > fd_max)
                        fd_max = sock_fd;
                    server_socket->client_mutex.insert(std::make_pair(sock_fd, new std::mutex));
                    server_socket->connect_cb(sock_fd);
                }else{
                    int32 sock_fd = i;
                    server_socket->client_mutex[sock_fd]->lock();
                    char read_buf[LINE_MAX];
                    memset(read_buf, 0, LINE_MAX);
                    int32 n_bytes = read(sock_fd, read_buf, LINE_MAX);
                    server_socket->client_mutex[sock_fd]->unlock();

                    if(n_bytes == -1 || n_bytes == 0)
                    {
                        server_socket->disconnect_cb(sock_fd);
                        server_socket->client_mutex[sock_fd]->lock();
                        close(sock_fd);
                        server_socket->client_mutex[sock_fd]->unlock();
                        delete server_socket->client_mutex[sock_fd];
                        server_socket->client_mutex.erase(sock_fd);
                        FD_CLR(sock_fd, &fds);
                        break;
                    }

                    std::string msg = read_buf;
                    while(std::string::npos != msg.find('\r'))
                        msg.erase(msg.find('\r'), 1);
                    while(std::string::npos != msg.find('\n'))
                    {
                        server_socket->receive_cb(msg.substr(0, msg.find('\n')), sock_fd);
                        msg = msg.substr(msg.find('\n')+1, std::string::npos);
                    }
                }
            }
        }
    }
    std::lock_guard<std::mutex> lock(server_socket->socket_mutex);
    close(server_socket->sock);
    return;
}
