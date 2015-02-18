#line 2 "LTE_fdd_enb_user.cc" // Make __FILE__ omit the path
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

    File: LTE_fdd_enb_user.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 user class.

    Revision History
    ----------    -------------    --------------------------------------------
    11/10/2013    Ben Wojtowicz    Created file
    05/04/2014    Ben Wojtowicz    Added radio bearer support.
    06/15/2014    Ben Wojtowicz    Added initialize routine.
    08/03/2014    Ben Wojtowicz    Refactored user identities.
    09/03/2014    Ben Wojtowicz    Added ciphering and integrity algorithm
                                   storing.
    11/01/2014    Ben Wojtowicz    Added more MME support.
    11/29/2014    Ben Wojtowicz    Added DRB setup/teardown and C-RNTI release
                                   timer support.
    12/16/2014    Ben Wojtowicz    Changed the delayed delete functionality.
    02/15/2015    Ben Wojtowicz    Added clear_rbs and fixed copy_rbs.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_user.h"
#include "LTE_fdd_enb_user_mgr.h"
#include "LTE_fdd_enb_timer_mgr.h"
#include "liblte_mme.h"
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


/*******************************************************************************
                              CLASS IMPLEMENTATIONS
*******************************************************************************/

/********************************/
/*    Constructor/Destructor    */
/********************************/
LTE_fdd_enb_user::LTE_fdd_enb_user()
{
    uint32 i;

    // Identity
    id_set      = false;
    guti_set    = false;
    temp_id     = 0;
    c_rnti_set  = false;
    ip_addr_set = false;

    // Security
    auth_vec_set = false;

    // Capabilities
    for(i=0; i<8; i++)
    {
        eea_support[i] = false;
        eia_support[i] = false;
        uea_support[i] = false;
        uia_support[i] = false;
        gea_support[i] = false;
    }
    uea_set = false;
    uia_set = false;
    gea_set = false;

    // Radio Bearers
    srb0 = new LTE_fdd_enb_rb(LTE_FDD_ENB_RB_SRB0, this);
    srb1 = NULL;
    srb2 = NULL;
    for(i=0; i<8; i++)
    {
        drb[i] = NULL;
    }

    // MME
    emm_cause                 = LIBLTE_MME_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS;
    attach_type               = 0;
    pdn_type                  = 0;
    eps_bearer_id             = 0;
    proc_transaction_id       = 0;
    eit_flag                  = false;
    protocol_cnfg_opts.N_opts = 0;

    // MAC
    dl_ndi = false;
    ul_ndi = false;

    // Generic
    N_del_ticks = 0;
}
LTE_fdd_enb_user::~LTE_fdd_enb_user()
{
    uint32 i;

    // Radio Bearers
    for(i=0; i<8; i++)
    {
        delete drb[i];
    }
    delete srb2;
    delete srb1;
    delete srb0;
}

/********************/
/*    Initialize    */
/********************/
void LTE_fdd_enb_user::init(void)
{
    uint32 i;

    // Radio Bearers
    for(i=0; i<8; i++)
    {
        delete drb[i];
        drb[i] = NULL;
    }
    delete srb2;
    srb2 = NULL;
    delete srb1;
    srb1 = NULL;
    srb0->set_mme_procedure(LTE_FDD_ENB_MME_PROC_IDLE);
    srb0->set_mme_state(LTE_FDD_ENB_MME_STATE_IDLE);
    srb0->set_rrc_procedure(LTE_FDD_ENB_RRC_PROC_IDLE);
    srb0->set_rrc_state(LTE_FDD_ENB_RRC_STATE_IDLE);

    // MME
    emm_cause                 = LIBLTE_MME_EMM_CAUSE_ROAMING_NOT_ALLOWED_IN_THIS_TRACKING_AREA;
    attach_type               = 0;
    pdn_type                  = 0;
    eps_bearer_id             = 0;
    proc_transaction_id       = 0;
    protocol_cnfg_opts.N_opts = 0;

    // MAC
    dl_ndi = false;
    ul_ndi = false;

    // Identity
    c_rnti     = 0xFFFF;
    c_rnti_set = false;
}

/******************/
/*    Identity    */
/******************/
void LTE_fdd_enb_user::set_id(LTE_FDD_ENB_USER_ID_STRUCT *identity)
{
    memcpy(&id, identity, sizeof(LTE_FDD_ENB_USER_ID_STRUCT));
    id_set = true;
}
LTE_FDD_ENB_USER_ID_STRUCT* LTE_fdd_enb_user::get_id(void)
{
    return(&id);
}
bool LTE_fdd_enb_user::is_id_set(void)
{
    return(id_set);
}
void LTE_fdd_enb_user::set_guti(LIBLTE_MME_EPS_MOBILE_ID_GUTI_STRUCT *_guti)
{
    memcpy(&guti, _guti, sizeof(LIBLTE_MME_EPS_MOBILE_ID_GUTI_STRUCT));
    guti_set = true;
}
LIBLTE_MME_EPS_MOBILE_ID_GUTI_STRUCT* LTE_fdd_enb_user::get_guti(void)
{
    return(&guti);
}
bool LTE_fdd_enb_user::is_guti_set(void)
{
    return(guti_set);
}
void LTE_fdd_enb_user::set_temp_id(uint64 id)
{
    temp_id = id;
}
uint64 LTE_fdd_enb_user::get_temp_id(void)
{
    return(temp_id);
}
std::string LTE_fdd_enb_user::get_imsi_str(void)
{
    return(boost::lexical_cast<std::string>(id.imsi));
}
uint64 LTE_fdd_enb_user::get_imsi_num(void)
{
    return(id.imsi);
}
std::string LTE_fdd_enb_user::get_imei_str(void)
{
    return(boost::lexical_cast<std::string>(id.imei));
}
uint64 LTE_fdd_enb_user::get_imei_num(void)
{
    return(id.imei);
}
void LTE_fdd_enb_user::set_c_rnti(uint16 _c_rnti)
{
    c_rnti     = _c_rnti;
    c_rnti_set = true;
}
uint16 LTE_fdd_enb_user::get_c_rnti(void)
{
    return(c_rnti);
}
bool LTE_fdd_enb_user::is_c_rnti_set(void)
{
    return(c_rnti_set);
}
void LTE_fdd_enb_user::start_c_rnti_release_timer(void)
{
    LTE_fdd_enb_timer_mgr *timer_mgr = LTE_fdd_enb_timer_mgr::get_instance();
    LTE_fdd_enb_timer_cb   timer_expiry_cb(&LTE_fdd_enb_timer_cb_wrapper<LTE_fdd_enb_user, &LTE_fdd_enb_user::handle_timer_expiry>, this);

    timer_mgr->start_timer(500, timer_expiry_cb, &c_rnti_timer_id);
}
void LTE_fdd_enb_user::set_ip_addr(uint32 addr)
{
    ip_addr     = addr;
    ip_addr_set = true;
}
uint32 LTE_fdd_enb_user::get_ip_addr(void)
{
    return(ip_addr);
}
bool LTE_fdd_enb_user::is_ip_addr_set(void)
{
    return(ip_addr_set);
}

/******************/
/*    Security    */
/******************/
void LTE_fdd_enb_user::set_auth_vec(LTE_FDD_ENB_AUTHENTICATION_VECTOR_STRUCT *av)
{
    memcpy(&auth_vec, av, sizeof(LTE_FDD_ENB_AUTHENTICATION_VECTOR_STRUCT));
    auth_vec_set = true;
}
LTE_FDD_ENB_AUTHENTICATION_VECTOR_STRUCT* LTE_fdd_enb_user::get_auth_vec(void)
{
    return(&auth_vec);
}
void LTE_fdd_enb_user::increment_nas_count_dl(void)
{
    if(auth_vec_set)
    {
        auth_vec.nas_count_dl++;
    }
}
void LTE_fdd_enb_user::increment_nas_count_ul(void)
{
    if(auth_vec_set)
    {
        auth_vec.nas_count_ul++;
    }
}
bool LTE_fdd_enb_user::is_auth_vec_set(void)
{
    return(auth_vec_set);
}

/**********************/
/*    Capabilities    */
/**********************/
void LTE_fdd_enb_user::set_eea_support(uint8 eea,
                                       bool  support)
{
    eea_support[eea] = support;
}
bool LTE_fdd_enb_user::get_eea_support(uint8 eea)
{
    return(eea_support[eea]);
}
void LTE_fdd_enb_user::set_eia_support(uint8 eia,
                                       bool  support)
{
    eia_support[eia] = support;
}
bool LTE_fdd_enb_user::get_eia_support(uint8 eia)
{
    return(eia_support[eia]);
}
void LTE_fdd_enb_user::set_uea_support(uint8 uea,
                                       bool  support)
{
    uea_support[uea] = support;
    uea_set          = true;
}
bool LTE_fdd_enb_user::get_uea_support(uint8 uea)
{
    return(uea_support[uea]);
}
bool LTE_fdd_enb_user::is_uea_set(void)
{
    return(uea_set);
}
void LTE_fdd_enb_user::set_uia_support(uint8 uia,
                                       bool  support)
{
    uia_support[uia] = support;
    uia_set          = true;
}
bool LTE_fdd_enb_user::get_uia_support(uint8 uia)
{
    return(uia_support[uia]);
}
bool LTE_fdd_enb_user::is_uia_set(void)
{
    return(uia_set);
}
void LTE_fdd_enb_user::set_gea_support(uint8 gea,
                                       bool  support)
{
    gea_support[gea] = support;
    gea_set          = true;
}
bool LTE_fdd_enb_user::get_gea_support(uint8 gea)
{
    return(gea_support[gea]);
}
bool LTE_fdd_enb_user::is_gea_set(void)
{
    return(gea_set);
}

/***********************/
/*    Radio Bearers    */
/***********************/
void LTE_fdd_enb_user::get_srb0(LTE_fdd_enb_rb **rb)
{
    *rb = srb0;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user::setup_srb1(LTE_fdd_enb_rb **rb)
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_RB_ALREADY_SETUP;

    if(NULL == srb1)
    {
        srb1 = new LTE_fdd_enb_rb(LTE_FDD_ENB_RB_SRB1, this);
        err  = LTE_FDD_ENB_ERROR_NONE;
    }
    *rb = srb1;

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user::teardown_srb1(void)
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_RB_NOT_SETUP;

    if(NULL != srb1)
    {
        delete srb1;
        err = LTE_FDD_ENB_ERROR_NONE;
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user::get_srb1(LTE_fdd_enb_rb **rb)
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_RB_NOT_SETUP;

    if(NULL != srb1)
    {
        err = LTE_FDD_ENB_ERROR_NONE;
    }
    *rb = srb1;

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user::setup_srb2(LTE_fdd_enb_rb **rb)
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_RB_ALREADY_SETUP;

    if(NULL == srb2)
    {
        srb2 = new LTE_fdd_enb_rb(LTE_FDD_ENB_RB_SRB2, this);
        err  = LTE_FDD_ENB_ERROR_NONE;
    }
    *rb = srb2;

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user::teardown_srb2(void)
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_RB_NOT_SETUP;

    if(NULL != srb2)
    {
        delete srb2;
        err = LTE_FDD_ENB_ERROR_NONE;
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user::get_srb2(LTE_fdd_enb_rb **rb)
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_RB_NOT_SETUP;

    if(NULL != srb2)
    {
        err = LTE_FDD_ENB_ERROR_NONE;
    }
    *rb = srb2;

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user::setup_drb(LTE_FDD_ENB_RB_ENUM   drb_id,
                                                   LTE_fdd_enb_rb      **rb)
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_RB_ALREADY_SETUP;

    if(LTE_FDD_ENB_RB_DRB1    <= drb_id &&
       LTE_FDD_ENB_RB_N_ITEMS >  drb_id)
    {
        if(NULL == drb[drb_id-LTE_FDD_ENB_RB_DRB1])
        {
            drb[drb_id-LTE_FDD_ENB_RB_DRB1] = new LTE_fdd_enb_rb(LTE_FDD_ENB_RB_DRB1, this);
            err                             = LTE_FDD_ENB_ERROR_NONE;
        }
        *rb = drb[drb_id-LTE_FDD_ENB_RB_DRB1];
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user::teardown_drb(LTE_FDD_ENB_RB_ENUM drb_id)
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_RB_NOT_SETUP;

    if(LTE_FDD_ENB_RB_DRB1    <= drb_id &&
       LTE_FDD_ENB_RB_N_ITEMS >  drb_id)
    {
        if(NULL != drb[drb_id-LTE_FDD_ENB_RB_DRB1])
        {
            delete drb[drb_id-LTE_FDD_ENB_RB_DRB1];
            err = LTE_FDD_ENB_ERROR_NONE;
        }
    }

    return(err);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_user::get_drb(LTE_FDD_ENB_RB_ENUM   drb_id,
                                                 LTE_fdd_enb_rb      **rb)
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_RB_NOT_SETUP;

    if(LTE_FDD_ENB_RB_DRB1    <= drb_id &&
       LTE_FDD_ENB_RB_N_ITEMS >  drb_id)
    {
        if(NULL != drb[drb_id-LTE_FDD_ENB_RB_DRB1])
        {
            err = LTE_FDD_ENB_ERROR_NONE;
        }
        *rb = drb[drb_id-LTE_FDD_ENB_RB_DRB1];
    }

    return(err);
}
void LTE_fdd_enb_user::copy_rbs(LTE_fdd_enb_user *user)
{
    uint32 i;

    delete srb0;
    user->get_srb0(&srb0);
    srb0->reset_user(this);
    delete srb1;
    user->get_srb1(&srb1);
    if(NULL != srb1)
    {
        srb1->reset_user(this);
    }
    delete srb2;
    user->get_srb2(&srb2);
    if(NULL != srb2)
    {
        srb2->reset_user(this);
    }
    for(i=0; i<8; i++)
    {
        delete drb[i];
        user->get_drb((LTE_FDD_ENB_RB_ENUM)(LTE_FDD_ENB_RB_DRB1+i), &drb[i]);
        if(NULL != drb[i])
        {
            drb[i]->reset_user(this);
        }
    }
}
void LTE_fdd_enb_user::clear_rbs(void)
{
    uint32 i;

    srb0 = new LTE_fdd_enb_rb(LTE_FDD_ENB_RB_SRB0, this);
    srb1 = NULL;
    srb2 = NULL;
    for(i=0; i<8; i++)
    {
        drb[i] = NULL;
    }
}

/*************/
/*    MME    */
/*************/
void LTE_fdd_enb_user::set_emm_cause(uint8 cause)
{
    emm_cause = cause;
}
uint8 LTE_fdd_enb_user::get_emm_cause(void)
{
    return(emm_cause);
}
void LTE_fdd_enb_user::set_attach_type(uint8 type)
{
    attach_type = type;
}
uint8 LTE_fdd_enb_user::get_attach_type(void)
{
    return(attach_type);
}
void LTE_fdd_enb_user::set_pdn_type(uint8 type)
{
    pdn_type = type;
}
uint8 LTE_fdd_enb_user::get_pdn_type(void)
{
    return(pdn_type);
}
void LTE_fdd_enb_user::set_eps_bearer_id(uint8 id)
{
    eps_bearer_id = id;
}
uint8 LTE_fdd_enb_user::get_eps_bearer_id(void)
{
    return(eps_bearer_id);
}
void LTE_fdd_enb_user::set_proc_transaction_id(uint8 id)
{
    proc_transaction_id = id;
}
uint8 LTE_fdd_enb_user::get_proc_transaction_id(void)
{
    return(proc_transaction_id);
}
void LTE_fdd_enb_user::set_esm_info_transfer(bool eit)
{
    eit_flag = eit;
}
bool LTE_fdd_enb_user::get_esm_info_transfer(void)
{
    return(eit_flag);
}
void LTE_fdd_enb_user::set_protocol_cnfg_opts(LIBLTE_MME_PROTOCOL_CONFIG_OPTIONS_STRUCT *pco)
{
    memcpy(&protocol_cnfg_opts, pco, sizeof(LIBLTE_MME_PROTOCOL_CONFIG_OPTIONS_STRUCT));
}
LIBLTE_MME_PROTOCOL_CONFIG_OPTIONS_STRUCT* LTE_fdd_enb_user::get_protocol_cnfg_opts(void)
{
    return(&protocol_cnfg_opts);
}

/*************/
/*    MAC    */
/*************/
bool LTE_fdd_enb_user::get_dl_ndi(void)
{
    return(dl_ndi);
}
void LTE_fdd_enb_user::flip_dl_ndi(void)
{
    dl_ndi ^= 1;
}
bool LTE_fdd_enb_user::get_ul_ndi(void)
{
    return(ul_ndi);
}
void LTE_fdd_enb_user::flip_ul_ndi(void)
{
    ul_ndi ^= 1;
}

/*****************/
/*    Generic    */
/*****************/
void LTE_fdd_enb_user::set_N_del_ticks(uint32 N_ticks)
{
    N_del_ticks = N_ticks;
}
uint32 LTE_fdd_enb_user::get_N_del_ticks(void)
{
    return(N_del_ticks);
}
void LTE_fdd_enb_user::handle_timer_expiry(uint32 timer_id)
{
    LTE_fdd_enb_user_mgr *user_mgr = LTE_fdd_enb_user_mgr::get_instance();

    if(timer_id == c_rnti_timer_id)
    {
        c_rnti_set = false;
        user_mgr->release_c_rnti(c_rnti);
    }
}
