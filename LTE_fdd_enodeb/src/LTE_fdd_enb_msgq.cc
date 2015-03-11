#line 2 "LTE_fdd_enb_msgq.cc" // Make __FILE__ omit the path
/*******************************************************************************

    Copyright 2013-2015 Ben Wojtowicz

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

    File: LTE_fdd_enb_msgq.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 message queues.

    Revision History
    ----------    -------------    --------------------------------------------
    11/10/2013    Ben Wojtowicz    Created file
    11/23/2013    Ben Wojtowicz    Fixed a bug with receive size.
    01/18/2014    Ben Wojtowicz    Added ability to set priorities.
    06/15/2014    Ben Wojtowicz    Omitting path from __FILE__.
    02/15/2015    Ben Wojtowicz    Moving to new message queue with semaphores
                                   and circular buffers.
    03/15/2015    Ben Wojtowicz    Added a mutex to the circular buffer.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_interface.h"
#include "LTE_fdd_enb_msgq.h"

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

/******************/
/*    Callback    */
/******************/
LTE_fdd_enb_msgq_cb::LTE_fdd_enb_msgq_cb()
{
}
LTE_fdd_enb_msgq_cb::LTE_fdd_enb_msgq_cb(FuncType f, void* o)
{
    func = f;
    obj  = o;
}
void LTE_fdd_enb_msgq_cb::operator()(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    return (*func)(obj, msg);
}

/********************************/
/*    Constructor/Destructor    */
/********************************/
LTE_fdd_enb_msgq::LTE_fdd_enb_msgq(std::string _msgq_name)
{
    sema      = new boost::interprocess::interprocess_semaphore(0);
    circ_buf  = new boost::circular_buffer<LTE_FDD_ENB_MESSAGE_STRUCT>(100);
    msgq_name = _msgq_name;
    rx_setup  = false;
}
LTE_fdd_enb_msgq::~LTE_fdd_enb_msgq()
{
    if(rx_setup)
    {
        send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
             LTE_FDD_ENB_DEST_LAYER_ANY,
             NULL,
             0);

        // Cleanup thread
        pthread_cancel(rx_thread);
        pthread_join(rx_thread, NULL);
        rx_setup = false;
    }
}

/***************/
/*    Setup    */
/***************/
void LTE_fdd_enb_msgq::attach_rx(LTE_fdd_enb_msgq_cb cb)
{
    callback = cb;
    prio     = 0;
    pthread_create(&rx_thread, NULL, &receive_thread, this);
    rx_setup = true;
}
void LTE_fdd_enb_msgq::attach_rx(LTE_fdd_enb_msgq_cb cb,
                                 uint32              _prio)
{
    callback = cb;
    prio     = _prio;
    pthread_create(&rx_thread, NULL, &receive_thread, this);
    rx_setup = true;
}

/**********************/
/*    Send/Receive    */
/**********************/
void LTE_fdd_enb_msgq::send(LTE_FDD_ENB_MESSAGE_TYPE_ENUM  type,
                            LTE_FDD_ENB_DEST_LAYER_ENUM    dest_layer,
                            LTE_FDD_ENB_MESSAGE_UNION     *msg_content,
                            uint32                         msg_content_size)
{
    LTE_FDD_ENB_MESSAGE_STRUCT msg;

    msg.type       = type;
    msg.dest_layer = dest_layer;
    if(msg_content != NULL)
    {
        memcpy(&msg.msg, msg_content, msg_content_size);
    }

    mutex.lock();
    circ_buf->push_back(msg);
    mutex.unlock();
    sema->post();
}
void LTE_fdd_enb_msgq::send(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    mutex.lock();
    circ_buf->push_back(msg);
    mutex.unlock();
    sema->post();
}
void* LTE_fdd_enb_msgq::receive_thread(void *inputs)
{
    LTE_fdd_enb_interface      *interface = LTE_fdd_enb_interface::get_instance();
    LTE_fdd_enb_msgq           *msgq      = (LTE_fdd_enb_msgq *)inputs;
    LTE_FDD_ENB_MESSAGE_STRUCT  msg;
    struct sched_param          priority;
    std::size_t                 rx_size;
    uint32                      prio;
    bool                        not_done = true;

    // Set priority
    if(msgq->prio != 0)
    {
        // FIXME: verify
        priority.sched_priority = prio;
        pthread_setschedparam(msgq->rx_thread, SCHED_FIFO, &priority);
    }

    while(not_done)
    {
        // Wait for a message
        msgq->sema->wait();
        msgq->mutex.lock();
        if(msgq->circ_buf->size() != 0)
        {
            while(msgq->circ_buf->size() != 0)
            {
                msg = msgq->circ_buf->front();
                msgq->circ_buf->pop_front();
                msgq->mutex.unlock();

                // Process message
                switch(msg.type)
                {
                case LTE_FDD_ENB_MESSAGE_TYPE_KILL:
                    not_done = false;
                    break;
                default:
                    msgq->callback(msg);
                    break;
                }

                msgq->mutex.lock();
            }
        }else{
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                      LTE_FDD_ENB_DEBUG_LEVEL_MSGQ,
                                      __FILE__,
                                      __LINE__,
                                      "%s circular buffer empty on receive",
                                      msgq->msgq_name.c_str());
        }
        msgq->mutex.unlock();
    }

    return(NULL);
}
