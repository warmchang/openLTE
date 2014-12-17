#line 2 "LTE_fdd_enb_gw.cc" // Make __FILE__ omit the path
/*******************************************************************************

    Copyright 2014 Ben Wojtowicz

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

    File: LTE_fdd_enb_gw.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 IP gateway.

    Revision History
    ----------    -------------    --------------------------------------------
    11/29/2014    Ben Wojtowicz    Created file
    12/16/2014    Ben Wojtowicz    Added ol extension to message queue.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_gw.h"
#include "LTE_fdd_enb_user_mgr.h"
#include "LTE_fdd_enb_cnfg_db.h"
#include <fcntl.h>
#include <arpa/inet.h>
#include <linux/ip.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

/*******************************************************************************
                              DEFINES
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              GLOBAL VARIABLES
*******************************************************************************/

LTE_fdd_enb_gw* LTE_fdd_enb_gw::instance = NULL;
boost::mutex    gw_instance_mutex;

/*******************************************************************************
                              CLASS IMPLEMENTATIONS
*******************************************************************************/

/*******************/
/*    Singleton    */
/*******************/
LTE_fdd_enb_gw* LTE_fdd_enb_gw::get_instance(void)
{
    boost::mutex::scoped_lock lock(gw_instance_mutex);

    if(NULL == instance)
    {
        instance = new LTE_fdd_enb_gw();
    }

    return(instance);
}
void LTE_fdd_enb_gw::cleanup(void)
{
    boost::mutex::scoped_lock lock(gw_instance_mutex);

    if(NULL != instance)
    {
        delete instance;
        instance = NULL;
    }
}

/********************************/
/*    Constructor/Destructor    */
/********************************/
LTE_fdd_enb_gw::LTE_fdd_enb_gw()
{
    started = false;
}
LTE_fdd_enb_gw::~LTE_fdd_enb_gw()
{
    stop();
}

/********************/
/*    Start/Stop    */
/********************/
bool LTE_fdd_enb_gw::is_started(void)
{
    boost::mutex::scoped_lock lock(start_mutex);

    return(started);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_gw::start(char *err_str)
{
    boost::mutex::scoped_lock  lock(start_mutex);
    LTE_fdd_enb_cnfg_db       *cnfg_db = LTE_fdd_enb_cnfg_db::get_instance();
    LTE_fdd_enb_msgq_cb        pdcp_cb(&LTE_fdd_enb_msgq_cb_wrapper<LTE_fdd_enb_gw, &LTE_fdd_enb_gw::handle_pdcp_msg>, this);
    struct ifreq               ifr;
    int32                      sock;
    char                       dev[IFNAMSIZ] = "tun_openlte";
    uint32                     ip_addr;

    if(!started)
    {
        started = true;

        cnfg_db->get_param(LTE_FDD_ENB_PARAM_IP_ADDR_START, ip_addr);

        // Construct the TUN device
        tun_fd = open("/dev/net/tun", O_RDWR);
        if(0 > tun_fd)
        {
            err_str = strerror(errno);
            started = false;
            return(LTE_FDD_ENB_ERROR_CANT_START);
        }
        memset(&ifr, 0, sizeof(ifr));
        ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
        strncpy(ifr.ifr_ifrn.ifrn_name, dev, IFNAMSIZ);
        if(0 > ioctl(tun_fd, TUNSETIFF, &ifr))
        {
            err_str = strerror(errno);
            started = false;
            close(tun_fd);
            return(LTE_FDD_ENB_ERROR_CANT_START);
        }

        // Setup the IP address range
        sock                                                   = socket(AF_INET, SOCK_DGRAM, 0);
        ifr.ifr_addr.sa_family                                 = AF_INET;
        ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr = htonl(ip_addr);
        if(0 > ioctl(sock, SIOCSIFADDR, &ifr))
        {
            err_str = strerror(errno);
            started = false;
            close(tun_fd);
            return(LTE_FDD_ENB_ERROR_CANT_START);
        }
        ifr.ifr_netmask.sa_family                                 = AF_INET;
        ((struct sockaddr_in *)&ifr.ifr_netmask)->sin_addr.s_addr = inet_addr("255.255.255.0");
        if(0 > ioctl(sock, SIOCSIFNETMASK, &ifr))
        {
            err_str = strerror(errno);
            started = false;
            close(tun_fd);
            return(LTE_FDD_ENB_ERROR_CANT_START);
        }

        // Bring up the interface
        if(0 > ioctl(sock, SIOCGIFFLAGS, &ifr))
        {
            err_str = strerror(errno);
            started = false;
            close(tun_fd);
            return(LTE_FDD_ENB_ERROR_CANT_START);
        }
        ifr.ifr_flags |= IFF_UP | IFF_RUNNING;
        if(0 > ioctl(sock, SIOCSIFFLAGS, &ifr))
        {
            err_str = strerror(errno);
            started = false;
            close(tun_fd);
            return(LTE_FDD_ENB_ERROR_CANT_START);
        }

        // Setup PDCP communication
        pdcp_comm_msgq = new LTE_fdd_enb_msgq("pdcp_gw_olmq",
                                              pdcp_cb);
        gw_pdcp_olmq   = new boost::interprocess::message_queue(boost::interprocess::open_only,
                                                                "gw_pdcp_olmq");

        // Setup a thread to receive packets from the TUN device
        pthread_create(&rx_thread, NULL, &receive_thread, this);
    }

    return(LTE_FDD_ENB_ERROR_NONE);
}
void LTE_fdd_enb_gw::stop(void)
{
    boost::mutex::scoped_lock lock(start_mutex);

    if(started)
    {
        started = false;
        start_mutex.unlock();
        pthread_cancel(rx_thread);
        pthread_join(rx_thread, NULL);

        // FIXME: TEAR DOWN TUN DEVICE

        delete pdcp_comm_msgq;
    }
}

/***********************/
/*    Communication    */
/***********************/
void LTE_fdd_enb_gw::handle_pdcp_msg(LTE_FDD_ENB_MESSAGE_STRUCT *msg)
{
    LTE_fdd_enb_interface *interface = LTE_fdd_enb_interface::get_instance();

    switch(msg->type)
    {
    case LTE_FDD_ENB_MESSAGE_TYPE_GW_DATA_READY:
        handle_gw_data(&msg->msg.gw_data_ready);
        delete msg;
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_GW,
                                  __FILE__,
                                  __LINE__,
                                  "Received invalid PDCP message %s",
                                  LTE_fdd_enb_message_type_text[msg->type]);
        delete msg;
        break;
    }
}

/*******************************/
/*    PDCP Message Handlers    */
/*******************************/
void LTE_fdd_enb_gw::handle_gw_data(LTE_FDD_ENB_GW_DATA_READY_MSG_STRUCT *gw_data)
{
    LTE_fdd_enb_interface  *interface = LTE_fdd_enb_interface::get_instance();
    LIBLTE_BYTE_MSG_STRUCT *msg;

    if(LTE_FDD_ENB_ERROR_NONE == gw_data->rb->get_next_gw_data_msg(&msg))
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_GW,
                                  __FILE__,
                                  __LINE__,
                                  msg,
                                  "Received GW data message for RNTI=%u and RB=%s",
                                  gw_data->user->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[gw_data->rb->get_rb_id()]);

        if(msg->N_bytes != write(tun_fd, msg->msg, msg->N_bytes))
        {
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                      LTE_FDD_ENB_DEBUG_LEVEL_GW,
                                      __FILE__,
                                      __LINE__,
                                      "Write failure");
        }

        // Delete the message
        gw_data->rb->delete_next_gw_data_msg();
    }
}

/********************/
/*    GW Receive    */
/********************/
void* LTE_fdd_enb_gw::receive_thread(void *inputs)
{
    LTE_fdd_enb_interface                      *interface = LTE_fdd_enb_interface::get_instance();
    LTE_fdd_enb_gw                             *gw        = (LTE_fdd_enb_gw *)inputs;
    LTE_fdd_enb_user_mgr                       *user_mgr  = LTE_fdd_enb_user_mgr::get_instance();
    LTE_FDD_ENB_PDCP_DATA_SDU_READY_MSG_STRUCT  pdcp_data_sdu;
    LIBLTE_BYTE_MSG_STRUCT                      msg;
    struct iphdr                               *ip_pkt;
    uint32                                      idx = 0;
    int32                                       N_bytes;

    while(gw->is_started())
    {
        N_bytes = read(gw->tun_fd, &msg.msg[idx], LIBLTE_MAX_MSG_SIZE);

        if(N_bytes > 0)
        {
            msg.N_bytes = idx + N_bytes;
            ip_pkt      = (struct iphdr*)msg.msg;

            // Check if entire packet was received
            if(ntohs(ip_pkt->tot_len) == msg.N_bytes)
            {
                // Find user and rb
                if(LTE_FDD_ENB_ERROR_NONE == user_mgr->find_user(ntohl(ip_pkt->daddr), &pdcp_data_sdu.user) &&
                   LTE_FDD_ENB_ERROR_NONE == pdcp_data_sdu.user->get_drb(LTE_FDD_ENB_RB_DRB1, &pdcp_data_sdu.rb))
                {
                    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                              LTE_FDD_ENB_DEBUG_LEVEL_GW,
                                              __FILE__,
                                              __LINE__,
                                              &msg,
                                              "Received IP packet for RNTI=%u and RB=%s",
                                              pdcp_data_sdu.user->get_c_rnti(),
                                              LTE_fdd_enb_rb_text[pdcp_data_sdu.rb->get_rb_id()]);

                    // Send message to PDCP
                    pdcp_data_sdu.rb->queue_pdcp_data_sdu(&msg);
                    LTE_fdd_enb_msgq::send(gw->gw_pdcp_olmq,
                                           LTE_FDD_ENB_MESSAGE_TYPE_PDCP_DATA_SDU_READY,
                                           LTE_FDD_ENB_DEST_LAYER_PDCP,
                                           (LTE_FDD_ENB_MESSAGE_UNION *)&pdcp_data_sdu,
                                           sizeof(LTE_FDD_ENB_PDCP_DATA_SDU_READY_MSG_STRUCT));
                }

                idx = 0;
            }else{
                idx = N_bytes;
            }
        }else{
            // Something bad has happened
            break;
        }
    }

    return(NULL);
}
