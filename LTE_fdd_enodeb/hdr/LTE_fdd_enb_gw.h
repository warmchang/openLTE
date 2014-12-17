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

    File: LTE_fdd_enb_gw.h

    Description: Contains all the definitions for the LTE FDD eNodeB
                 IP gateway.

    Revision History
    ----------    -------------    --------------------------------------------
    11/29/2014    Ben Wojtowicz    Created file
    12/16/2014    Ben Wojtowicz    Added ol extension to message queue.

*******************************************************************************/

#ifndef __LTE_FDD_ENB_GW_H__
#define __LTE_FDD_ENB_GW_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_interface.h"
#include "LTE_fdd_enb_msgq.h"

/*******************************************************************************
                              DEFINES
*******************************************************************************/


/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_enb_gw
{
public:
    // Singleton
    static LTE_fdd_enb_gw* get_instance(void);
    static void cleanup(void);

    // Start/Stop
    bool is_started(void);
    LTE_FDD_ENB_ERROR_ENUM start(char *err_str);
    void stop(void);

private:
    // Singleton
    static LTE_fdd_enb_gw *instance;
    LTE_fdd_enb_gw();
    ~LTE_fdd_enb_gw();

    // Start/Stop
    boost::mutex start_mutex;
    bool         started;

    // Communication
    void handle_pdcp_msg(LTE_FDD_ENB_MESSAGE_STRUCT *msg);
    LTE_fdd_enb_msgq                   *pdcp_comm_msgq;
    boost::interprocess::message_queue *gw_pdcp_olmq;

    // PDCP Message Handlers
    void handle_gw_data(LTE_FDD_ENB_GW_DATA_READY_MSG_STRUCT *gw_data);

    // GW Receive
    static void* receive_thread(void *inputs);
    pthread_t rx_thread;

    // TUN device
    int32 tun_fd;
};

#endif /* __LTE_FDD_ENB_GW_H__ */
