#line 2 "LTE_fdd_enb_user_mgr.cc" // Make __FILE__ omit the path
/*******************************************************************************

    Copyright 2013-2014 Ben Wojtowicz

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

    File: LTE_fdd_enb_user_mgr.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 user manager.

    Revision History
    ----------    -------------    --------------------------------------------
    11/10/2013    Ben Wojtowicz    Created file
    01/18/2014    Ben Wojtowicz    Added level to debug prints.
    05/04/2014    Ben Wojtowicz    Added C-RNTI timeout timers.
    06/15/2014    Ben Wojtowicz    Deleting user on C-RNTI expiration.
    08/03/2014    Ben Wojtowicz    Refactored add_user.
    11/01/2014    Ben Wojtowicz    Added M-TMSI assignment.
    11/29/2014    Ben Wojtowicz    Refactored C-RNTI assign/release, added
                                   C-RNTI transfer, added more ways to add,
                                   delete, and find users.
    12/16/2014    Ben Wojtowicz    Added delayed user delete functionality.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_user_mgr.h"
#include "LTE_fdd_enb_timer_mgr.h"
#include "liblte_mac.h"
#include <boost/lexical_cast.hpp>

/*******************************************************************************
                              DEFINES
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              GLOBAL VARIABLES
*******************************************************************************/

LTE_fdd_enb_user_mgr* LTE_fdd_enb_user_mgr::instance = NULL;
boost::mutex          user_mgr_instance_mutex;

/*******************************************************************************
                              CLASS IMPLEMENTATIONS
*******************************************************************************/

/*******************/
/*    Singleton    */
/*******************/
LTE_fdd_enb_user_mgr* LTE_fdd_enb_user_mgr::get_instance(void)
{
    boost::mutex::scoped_lock lock(user_mgr_instance_mutex);

    if(NULL == instance)
    {
        instance = new LTE_fdd_enb_user_mgr();
    }

    return(instance);
}
void LTE_fdd_enb_user_mgr::cleanup(void)
{
    boost::mutex::scoped_lock lock(user_mgr_instance_mutex);

    if(NULL != instance)
    {
        delete instance;
        instance = NULL;
    }
}

/********************************/
/*    Constructor/Destructor    */
/********************************/
LTE_fdd_enb_user_mgr::LTE_fdd_enb_user_mgr()
{
    next_m_tmsi = 1;
    next_c_rnti = LIBLTE_MAC_C_RNTI_START;
}
LTE_fdd_enb_user_mgr::~LTE_fdd_enb_user_mgr()
{
}

/****************************/
/*    External Interface    */
/****************************/
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::assign_c_rnti(LTE_fdd_enb_user *user,
                                                           uint16           *c_rnti)
{
    boost::mutex::scoped_lock                      lock(c_rnti_mutex);
    LTE_fdd_enb_interface                         *interface    = LTE_fdd_enb_interface::get_instance();
    std::map<uint16, LTE_fdd_enb_user*>::iterator  iter         = c_rnti_map.find(next_c_rnti);
    LTE_FDD_ENB_ERROR_ENUM                         err          = LTE_FDD_ENB_ERROR_NO_FREE_C_RNTI;
    uint16                                         start_c_rnti = next_c_rnti++;

    if(LIBLTE_MAC_C_RNTI_END < next_c_rnti)
    {
        next_c_rnti = LIBLTE_MAC_C_RNTI_START;
    }
    while(c_rnti_map.end() != iter)
    {
        next_c_rnti++;
        if(LIBLTE_MAC_C_RNTI_END < next_c_rnti)
        {
            next_c_rnti = LIBLTE_MAC_C_RNTI_START;
        }
        if(next_c_rnti == start_c_rnti)
        {
            break;
        }

        iter = c_rnti_map.find(next_c_rnti);
    }

    if(next_c_rnti != start_c_rnti)
    {
        c_rnti_map[next_c_rnti] = user;
        *c_rnti                 = next_c_rnti++;
        err                     = LTE_FDD_ENB_ERROR_NONE;

        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_USER,
                                  __FILE__,
                                  __LINE__,
                                  "C-RNTI=%u assigned",
                                  *c_rnti);

        if(LIBLTE_MAC_C_RNTI_END < next_c_rnti)
        {
            next_c_rnti = LIBLTE_MAC_C_RNTI_START;
        }
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::release_c_rnti(uint16 c_rnti)
{
    boost::mutex::scoped_lock                      lock(c_rnti_mutex);
    boost::mutex::scoped_lock                      t_lock(timer_id_mutex);
    LTE_fdd_enb_interface                         *interface = LTE_fdd_enb_interface::get_instance();
    LTE_fdd_enb_timer_mgr                         *timer_mgr = LTE_fdd_enb_timer_mgr::get_instance();
    std::map<uint16, LTE_fdd_enb_user*>::iterator  iter      = c_rnti_map.find(c_rnti);
    std::map<uint16, uint32>::iterator             tr_iter;
    std::map<uint32, uint16>::iterator             tf_iter;
    LTE_FDD_ENB_ERROR_ENUM                         err = LTE_FDD_ENB_ERROR_C_RNTI_NOT_FOUND;

    if(c_rnti_map.end() != iter)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_USER,
                                  __FILE__,
                                  __LINE__,
                                  "C-RNTI=%u released",
                                  c_rnti);

        // Initialize or delete the user
        if((*iter).second->is_id_set())
        {
            (*iter).second->init();
        }else{
            del_user((*iter).second, false);
        }

        // Release the C-RNTI
        c_rnti_map.erase(iter);

        // Stop the C-RNTI timer
        tr_iter = timer_id_map_reverse.find(c_rnti);
        if(timer_id_map_reverse.end() != tr_iter)
        {
            timer_mgr->stop_timer((*tr_iter).second);
            tf_iter = timer_id_map_forward.find((*tr_iter).second);
            if(timer_id_map_forward.end() != tf_iter)
            {
                timer_id_map_forward.erase(tf_iter);
            }
            timer_id_map_reverse.erase(tr_iter);
        }

        err = LTE_FDD_ENB_ERROR_NONE;
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::transfer_c_rnti(LTE_fdd_enb_user *old_user,
                                                             LTE_fdd_enb_user *new_user)
{
    boost::mutex::scoped_lock                     lock(c_rnti_mutex);
    std::map<uint16, LTE_fdd_enb_user*>::iterator iter = c_rnti_map.find(old_user->get_c_rnti());
    LTE_FDD_ENB_ERROR_ENUM                        err  = LTE_FDD_ENB_ERROR_C_RNTI_NOT_FOUND;
    uint16                                        c_rnti;

    if(c_rnti_map.end() != iter)
    {
        c_rnti = old_user->get_c_rnti();

        // Cleanup the old user
        if(old_user->is_id_set())
        {
            old_user->init();
        }else{
            del_user(old_user, true);
        }

        // Update the C-RNTI map
        c_rnti_map.erase(iter);
        c_rnti_map[c_rnti] = new_user;
        new_user->set_c_rnti(c_rnti);

        err = LTE_FDD_ENB_ERROR_NONE;
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::reset_c_rnti_timer(uint16 c_rnti)
{
    boost::mutex::scoped_lock           lock(timer_id_mutex);
    std::map<uint16, uint32>::iterator  iter      = timer_id_map_reverse.find(c_rnti);
    LTE_fdd_enb_timer_mgr              *timer_mgr = LTE_fdd_enb_timer_mgr::get_instance();
    LTE_FDD_ENB_ERROR_ENUM              err       = LTE_FDD_ENB_ERROR_C_RNTI_NOT_FOUND;

    if(timer_id_map_reverse.end() != iter)
    {
        timer_mgr->reset_timer((*iter).second);

        err = LTE_FDD_ENB_ERROR_NONE;
    }

    return(err);
}
uint32 LTE_fdd_enb_user_mgr::get_next_m_tmsi(void)
{
    return(next_m_tmsi++);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::add_user(LTE_fdd_enb_user **user)
{
    LTE_fdd_enb_interface  *interface = LTE_fdd_enb_interface::get_instance();
    LTE_fdd_enb_timer_mgr  *timer_mgr = LTE_fdd_enb_timer_mgr::get_instance();
    LTE_fdd_enb_user       *new_user  = NULL;
    LTE_fdd_enb_timer_cb    timer_expiry_cb(&LTE_fdd_enb_timer_cb_wrapper<LTE_fdd_enb_user_mgr, &LTE_fdd_enb_user_mgr::handle_c_rnti_timer_expiry>, this);
    LTE_FDD_ENB_ERROR_ENUM  err       = LTE_FDD_ENB_ERROR_NONE;
    uint32                  timer_id;
    uint16                  c_rnti;

    new_user = new LTE_fdd_enb_user();

    if(NULL != new_user)
    {
        // Assign C-RNTI
        if(LTE_FDD_ENB_ERROR_NONE == assign_c_rnti(new_user, &c_rnti))
        {
            // Start C-RNTI reservation timer
            timer_mgr->start_timer(5000, timer_expiry_cb, &timer_id);
            timer_id_mutex.lock();
            timer_id_map_forward[timer_id] = c_rnti;
            timer_id_map_reverse[c_rnti]   = timer_id;
            timer_id_mutex.unlock();

            // Setup user
            new_user->set_c_rnti(c_rnti);

            // Store user
            user_mutex.lock();
            user_list.push_back(new_user);
            user_mutex.unlock();

            // Return user
            *user = new_user;
        }else{
            err = LTE_FDD_ENB_ERROR_NO_FREE_C_RNTI;
            delete new_user;
        }
    }else{
        err = LTE_FDD_ENB_ERROR_BAD_ALLOC;
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::find_user(std::string        imsi,
                                                       LTE_fdd_enb_user **user)
{
    boost::mutex::scoped_lock               lock(user_mutex);
    std::list<LTE_fdd_enb_user*>::iterator  iter;
    LTE_FDD_ENB_ERROR_ENUM                  err      = LTE_FDD_ENB_ERROR_USER_NOT_FOUND;
    const char                             *imsi_str = imsi.c_str();
    uint64                                  imsi_num = 0;
    uint32                                  i;

    if(imsi.length() == 15)
    {
        for(i=0; i<15; i++)
        {
            imsi_num *= 10;
            imsi_num += imsi_str[i] - '0';
        }

        for(iter=user_list.begin(); iter!=user_list.end(); iter++)
        {
            if((*iter)->is_id_set() &&
               (*iter)->get_id()->imsi == imsi_num)
            {
                *user = (*iter);
                err   = LTE_FDD_ENB_ERROR_NONE;
                break;
            }
        }
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::find_user(uint16             c_rnti,
                                                       LTE_fdd_enb_user **user)
{
    boost::mutex::scoped_lock              lock(user_mutex);
    std::list<LTE_fdd_enb_user*>::iterator iter;
    LTE_FDD_ENB_ERROR_ENUM                 err = LTE_FDD_ENB_ERROR_USER_NOT_FOUND;

    for(iter=user_list.begin(); iter!=user_list.end(); iter++)
    {
        if((*iter)->is_c_rnti_set() &&
           (*iter)->get_c_rnti() == c_rnti)
        {
            *user = (*iter);
            err   = LTE_FDD_ENB_ERROR_NONE;
            break;
        }
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::find_user(LIBLTE_MME_EPS_MOBILE_ID_GUTI_STRUCT  *guti,
                                                       LTE_fdd_enb_user                     **user)
{
    boost::mutex::scoped_lock              lock(user_mutex);
    std::list<LTE_fdd_enb_user*>::iterator iter;
    LTE_FDD_ENB_ERROR_ENUM                 err = LTE_FDD_ENB_ERROR_USER_NOT_FOUND;

    for(iter=user_list.begin(); iter!=user_list.end(); iter++)
    {
        if((*iter)->is_guti_set()                                  &&
           (*iter)->get_guti()->m_tmsi       == guti->m_tmsi       &&
           (*iter)->get_guti()->mcc          == guti->mcc          &&
           (*iter)->get_guti()->mnc          == guti->mnc          &&
           (*iter)->get_guti()->mme_group_id == guti->mme_group_id &&
           (*iter)->get_guti()->mme_code     == guti->mme_code)
        {
            *user = (*iter);
            err   = LTE_FDD_ENB_ERROR_NONE;
            break;
        }
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::find_user(LIBLTE_RRC_S_TMSI_STRUCT  *s_tmsi,
                                                       LTE_fdd_enb_user         **user)
{
    boost::mutex::scoped_lock              lock(user_mutex);
    std::list<LTE_fdd_enb_user*>::iterator iter;
    LTE_FDD_ENB_ERROR_ENUM                 err = LTE_FDD_ENB_ERROR_USER_NOT_FOUND;

    for(iter=user_list.begin(); iter!=user_list.end(); iter++)
    {
        if((*iter)->is_guti_set()                          &&
           (*iter)->get_guti()->m_tmsi   == s_tmsi->m_tmsi &&
           (*iter)->get_guti()->mme_code == s_tmsi->mmec)
        {
            *user = (*iter);
            err   = LTE_FDD_ENB_ERROR_NONE;
            break;
        }
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::find_user(uint32             ip_addr,
                                                       LTE_fdd_enb_user **user)
{
    boost::mutex::scoped_lock              lock(user_mutex);
    std::list<LTE_fdd_enb_user*>::iterator iter;
    LTE_FDD_ENB_ERROR_ENUM                 err = LTE_FDD_ENB_ERROR_USER_NOT_FOUND;

    for(iter=user_list.begin(); iter!=user_list.end(); iter++)
    {
        if((*iter)->is_ip_addr_set() &&
           (*iter)->get_ip_addr() == ip_addr)
        {
            *user = (*iter);
            err   = LTE_FDD_ENB_ERROR_NONE;
            break;
        }
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::del_user(LTE_fdd_enb_user *user,
                                                      bool              delayed)
{
    boost::mutex::scoped_lock               lock(user_mutex);
    std::list<LTE_fdd_enb_user*>::iterator  iter;
    LTE_fdd_enb_user                       *tmp_user = NULL;
    LTE_FDD_ENB_ERROR_ENUM                  err      = LTE_FDD_ENB_ERROR_USER_NOT_FOUND;

    if(user->is_id_set())
    {
        for(iter=user_list.begin(); iter!=user_list.end(); iter++)
        {
            if(user->get_id()->imsi == (*iter)->get_id()->imsi &&
               user->get_id()->imei == (*iter)->get_id()->imei)
            {
                tmp_user = (*iter);
                user_list.erase(iter);
                if(delayed)
                {
                    delayed_del_user_list.push_back(tmp_user);
                }else{
                    delete tmp_user;
                }
                err = LTE_FDD_ENB_ERROR_NONE;
                break;
            }
        }
    }else if(user->is_guti_set()){
        for(iter=user_list.begin(); iter!=user_list.end(); iter++)
        {
            if(user->get_guti()->m_tmsi       == (*iter)->get_guti()->m_tmsi       &&
               user->get_guti()->mcc          == (*iter)->get_guti()->mcc          &&
               user->get_guti()->mnc          == (*iter)->get_guti()->mnc          &&
               user->get_guti()->mme_group_id == (*iter)->get_guti()->mme_group_id &&
               user->get_guti()->mme_code     == (*iter)->get_guti()->mme_code)
            {
                tmp_user = (*iter);
                user_list.erase(iter);
                if(delayed)
                {
                    delayed_del_user_list.push_back(tmp_user);
                }else{
                    delete tmp_user;
                }
                err = LTE_FDD_ENB_ERROR_NONE;
                break;
            }
        }
    }else if(user->is_c_rnti_set()){
        for(iter=user_list.begin(); iter!=user_list.end(); iter++)
        {
            if(user->get_c_rnti() == (*iter)->get_c_rnti())
            {
                tmp_user = (*iter);
                user_list.erase(iter);
                if(delayed)
                {
                    delayed_del_user_list.push_back(tmp_user);
                }else{
                    delete tmp_user;
                }
                err = LTE_FDD_ENB_ERROR_NONE;
                break;
            }
        }
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::del_user(std::string imsi,
                                                      bool        delayed)
{
    boost::mutex::scoped_lock               lock(user_mutex);
    std::list<LTE_fdd_enb_user*>::iterator  iter;
    LTE_fdd_enb_user                       *tmp_user = NULL;
    LTE_FDD_ENB_ERROR_ENUM                  err      = LTE_FDD_ENB_ERROR_USER_NOT_FOUND;
    const char                             *imsi_str = imsi.c_str();
    uint64                                  imsi_num = 0;
    uint32                                  i;

    if(imsi.length() == 15)
    {
        for(i=0; i<15; i++)
        {
            imsi_num *= 10;
            imsi_num += imsi_str[i] - '0';
        }

        for(iter=user_list.begin(); iter!=user_list.end(); iter++)
        {
            if((*iter)->is_id_set() &&
               (*iter)->get_id()->imsi == imsi_num)
            {
                tmp_user = (*iter);
                user_list.erase(iter);
                if(delayed)
                {
                    delayed_del_user_list.push_back(tmp_user);
                }else{
                    delete tmp_user;
                }
                err = LTE_FDD_ENB_ERROR_NONE;
                break;
            }
        }
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::del_user(uint16 c_rnti,
                                                      bool   delayed)
{
    boost::mutex::scoped_lock               lock(user_mutex);
    std::list<LTE_fdd_enb_user*>::iterator  iter;
    LTE_fdd_enb_user                       *tmp_user = NULL;
    LTE_FDD_ENB_ERROR_ENUM                  err      = LTE_FDD_ENB_ERROR_USER_NOT_FOUND;

    for(iter=user_list.begin(); iter!=user_list.end(); iter++)
    {
        if((*iter)->is_c_rnti_set() &&
           (*iter)->get_c_rnti() == c_rnti)
        {
            tmp_user = (*iter);
            user_list.erase(iter);
            if(delayed)
            {
                delayed_del_user_list.push_back(tmp_user);
            }else{
                delete tmp_user;
            }
            err = LTE_FDD_ENB_ERROR_NONE;
            break;
        }
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user_mgr::del_user(LIBLTE_MME_EPS_MOBILE_ID_GUTI_STRUCT *guti,
                                                      bool                                  delayed)
{
    boost::mutex::scoped_lock               lock(user_mutex);
    std::list<LTE_fdd_enb_user*>::iterator  iter;
    LTE_fdd_enb_user                       *tmp_user = NULL;
    LTE_FDD_ENB_ERROR_ENUM                  err      = LTE_FDD_ENB_ERROR_USER_NOT_FOUND;

    for(iter=user_list.begin(); iter!=user_list.end(); iter++)
    {
        if((*iter)->is_guti_set()                                  &&
           (*iter)->get_guti()->m_tmsi       == guti->m_tmsi       &&
           (*iter)->get_guti()->mcc          == guti->mcc          &&
           (*iter)->get_guti()->mnc          == guti->mnc          &&
           (*iter)->get_guti()->mme_group_id == guti->mme_group_id &&
           (*iter)->get_guti()->mme_code     == guti->mme_code)
        {
            tmp_user = (*iter);
            user_list.erase(iter);
            if(delayed)
            {
                delayed_del_user_list.push_back(tmp_user);
            }else{
                delete tmp_user;
            }
            err = LTE_FDD_ENB_ERROR_NONE;
            break;
        }
    }

    return(err);
}
void LTE_fdd_enb_user_mgr::handle_tick(void)
{
    LTE_fdd_enb_user *tmp_user;
    uint32            i;
    uint32            size = delayed_del_user_list.size();

    for(i=0; i<size; i++)
    {
        tmp_user = delayed_del_user_list.front();
        delayed_del_user_list.pop_front();
        if(tmp_user->get_N_del_ticks() > 100)
        {
            delete tmp_user;
        }else{
            tmp_user->set_N_del_ticks(tmp_user->get_N_del_ticks()+1);
            delayed_del_user_list.push_back(tmp_user);
        }
    }
}

/**********************/
/*    C-RNTI Timer    */
/**********************/
void LTE_fdd_enb_user_mgr::handle_c_rnti_timer_expiry(uint32 timer_id)
{
    LTE_fdd_enb_interface              *interface = LTE_fdd_enb_interface::get_instance();
    boost::mutex::scoped_lock           lock(timer_id_mutex);
    std::map<uint32, uint16>::iterator  forward_iter = timer_id_map_forward.find(timer_id);
    std::map<uint16, uint32>::iterator  reverse_iter;
    uint16                              c_rnti;

    if(timer_id_map_forward.end() != forward_iter)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_USER,
                                  __FILE__,
                                  __LINE__,
                                  "C-RNTI allocation timer expiry C-RNTI=%u",
                                  (*forward_iter).second);
        c_rnti = (*forward_iter).second;
        reverse_iter = timer_id_map_reverse.find((*forward_iter).second);
        if(timer_id_map_reverse.end() != reverse_iter)
        {
            timer_id_map_reverse.erase(reverse_iter);
        }
        timer_id_map_forward.erase(forward_iter);

        timer_id_mutex.unlock();
        release_c_rnti(c_rnti);
    }
}
