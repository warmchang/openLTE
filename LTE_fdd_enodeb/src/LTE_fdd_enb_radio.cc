#line 2 "LTE_fdd_enb_radio.cc" // Make __FILE__ omit the path
/*******************************************************************************

    Copyright 2013-2017, 2021 Ben Wojtowicz
    Copyright 2016 Przemek Bereski (bladeRF support)

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

    File: LTE_fdd_enb_radio.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 radio device control.

    Revision History
    ----------    -------------    --------------------------------------------
    11/10/2013    Ben Wojtowicz    Created file
    12/30/2013    Ben Wojtowicz    Changed the setting of the thread priority
                                   to use the uhd method and fixed a bug with
                                   baseband saturation in transmit.
    01/18/2014    Ben Wojtowicz    Handling multiple antennas, added ability to
                                   update EARFCNs, and fixed sleep time for
                                   no_rf case.
    04/12/2014    Ben Wojtowicz    Pulled in a patch from Max Suraev for more
                                   descriptive start failures.
    06/15/2014    Ben Wojtowicz    Changed fn_combo to current_tti.
    07/22/2014    Ben Wojtowicz    Added clock source as a configurable
                                   parameter.
    08/03/2014    Ben Wojtowicz    Fixed clock_source bug.
    09/03/2014    Ben Wojtowicz    Fixed stop issue.
    12/16/2014    Ben Wojtowicz    Pulled in a patch from Ruben Merz to add
                                   USRP X300 support.
    12/24/2014    Ben Wojtowicz    Added more time spec information in debug.
    07/25/2015    Ben Wojtowicz    Added parameters to abstract PHY sample rate
                                   from radio sample rate.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t and
                                   sem_t.
    07/03/2016    Ben Wojtowicz    Massive restructuring to support the addition
                                   of bladeRF as a radio choice and setting
                                   processor affinity.
    07/03/2016    Przemek Bereski  Addition of bladeRF as a radio choice.
    10/09/2016    Ben Wojtowicz    Added typecast for bladerf_get_timestamp().
    07/29/2017    Ben Wojtowicz    Using the latest tools library.
    02/14/2021    Ben Wojtowicz    Massive reformat and using the new RRC
                                   library.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_radio.h"
#include "LTE_fdd_enb_phy.h"
#include "liblte_interface.h"
#include "libtools_helpers.h"
#include <uhd/device.hpp>
#include <uhd/types/device_addr.hpp>
#include <uhd/property_tree.hpp>
#include <uhd/utils/thread.hpp>
#include <thread>

/*******************************************************************************
                              DEFINES
*******************************************************************************/

// Change this to 1 to turn on RADIO DEBUG
#define EXTRA_RX_RADIO_DEBUG 0
#define EXTRA_TX_RADIO_DEBUG 0

// bladeRF defines
#define BLADERF_NUM_BUFFERS   256
#define BLADERF_NUM_TRANSFERS 32
#define BLADERF_TIMEOUT_MS    4000

/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              GLOBAL VARIABLES
*******************************************************************************/


/*******************************************************************************
                              LOCAL FUNCTIONS
*******************************************************************************/

static uint32 find_usrps(LTE_FDD_ENB_AVAILABLE_RADIOS_STRUCT *radios)
{
    uhd::device_addr_t  hint;
    uhd::device_addrs_t devs = uhd::device::find(hint);

    if(NULL != radios)
    {
        for(size_t i=0; i<devs.size(); i++)
        {
            radios->radio[radios->num_radios].name   = devs[i].to_string();
            radios->radio[radios->num_radios++].type = LTE_FDD_ENB_RADIO_TYPE_USRP_B2X0;
        }
    }

    return devs.size();
}

static uint32 find_usrps()
{
    return find_usrps(NULL);
}

static uint32 find_bladerfs(LTE_FDD_ENB_AVAILABLE_RADIOS_STRUCT *radios)
{
    struct bladerf_devinfo *devs;
    int                     N_devs = bladerf_get_device_list(&devs);
    if(N_devs < 0)
        return 0;
    if(NULL != radios)
    {
        for(int i=0; i<N_devs; i++)
        {
            radios->radio[radios->num_radios].name    = "bladerf-";
            radios->radio[radios->num_radios].name   += devs[i].serial;
            radios->radio[radios->num_radios++].type  = LTE_FDD_ENB_RADIO_TYPE_BLADERF;
        }
    }
    bladerf_free_device_list(devs);

    return N_devs;
}

static uint32 find_bladerfs()
{
    return find_bladerfs(NULL);
}

/*******************************************************************************
                              CLASS IMPLEMENTATIONS
*******************************************************************************/

/**************************************/
/*    No-RF Constructor/Destructor    */
/**************************************/
LTE_fdd_enb_radio_no_rf::LTE_fdd_enb_radio_no_rf()
{
    // Sleep time between subframes
    sleep_time.tv_sec  = 0;
    sleep_time.tv_nsec = 1000000;
}
LTE_fdd_enb_radio_no_rf::~LTE_fdd_enb_radio_no_rf()
{
}

/*******************************/
/*    No-RF Radio Functions    */
/*******************************/
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio_no_rf::setup()
{
    return LTE_FDD_ENB_ERROR_NONE;
}
void LTE_fdd_enb_radio_no_rf::teardown()
{
}
void LTE_fdd_enb_radio_no_rf::send()
{
}
void LTE_fdd_enb_radio_no_rf::init(LTE_FDD_ENB_RADIO_PARAMS_STRUCT *radio_params)
{
}
void LTE_fdd_enb_radio_no_rf::receive(LTE_FDD_ENB_RADIO_PARAMS_STRUCT *radio_params)
{
    if(radio_params->init_needed)
    {
        // Signal PHY to generate first subframe
        radio_params->phy->radio_interface(&radio_params->tx_radio_buf[1]);
        radio_params->init_needed = false;
    }
    radio_params->rx_radio_buf[radio_params->buf_idx].current_tti = radio_params->rx_current_tti;
    radio_params->phy->radio_interface(&radio_params->tx_radio_buf[radio_params->buf_idx],
                                       &radio_params->rx_radio_buf[radio_params->buf_idx]);
    radio_params->buf_idx        = (radio_params->buf_idx + 1) % 2;
    radio_params->rx_current_tti = liblte_phy_add_to_tti(radio_params->rx_current_tti, 1);
    struct timespec time_rem;
    nanosleep(&sleep_time, &time_rem);

    if(radio_params->rx_current_tti == 4000)
        radio_params->rx_current_tti = liblte_phy_add_to_tti(radio_params->rx_current_tti, 20);
}

/******************************************/
/*    USRP-B2X0 Constructor/Destructor    */
/******************************************/
LTE_fdd_enb_radio_usrp_b2x0::LTE_fdd_enb_radio_usrp_b2x0()
{
}
LTE_fdd_enb_radio_usrp_b2x0::~LTE_fdd_enb_radio_usrp_b2x0()
{
}

/***********************************/
/*    USRP-B2X0 Radio Functions    */
/***********************************/
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio_usrp_b2x0::setup(uint32       idx,
                                                          uint32       bw,
                                                          int16        dl_earfcn,
                                                          int16        ul_earfcn,
                                                          std::string *clock_src,
                                                          uint32       samp_rate,
                                                          uint32       tx_gain,
                                                          uint32       rx_gain)
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_CANT_START;

    try
    {
        uhd::device_addr_t  hint;
        uhd::device_addrs_t devs = uhd::device::find(hint);
        // Setup the USRP
        bool master_clock_set = false;
        if(devs[idx-1]["type"] == "x300")
        {
            devs[idx-1]["master_clock_rate"] = "184320000";
            master_clock_set                 = true;
        }
        usrp = uhd::usrp::multi_usrp::make(devs[idx-1]);
        usrp->set_clock_source(*clock_src);
        if(!master_clock_set)
        {
            usrp->set_master_clock_rate(30720000);
            if(2.0 >= fabs(usrp->get_master_clock_rate() - 30720000.0))
                master_clock_set = true;
        }
        if(master_clock_set)
        {
            usrp->set_tx_rate(samp_rate);
            usrp->set_rx_rate(samp_rate);
            usrp->set_tx_freq((double)liblte_interface_dl_earfcn_to_frequency(dl_earfcn));
            usrp->set_rx_freq((double)liblte_interface_ul_earfcn_to_frequency(ul_earfcn));
            usrp->set_tx_gain(tx_gain);
            usrp->set_rx_gain(rx_gain);

            // Setup the TX and RX streams
            uhd::stream_args_t stream_args("fc32");
            tx_stream  = usrp->get_tx_stream(stream_args);
            rx_stream  = usrp->get_rx_stream(stream_args);
            N_tx_samps = tx_stream->get_max_num_samps();
            N_rx_samps = rx_stream->get_max_num_samps();
            if(N_rx_samps > LIBLTE_PHY_N_SAMPS_PER_SUBFR_1_92MHZ &&
               N_tx_samps > LIBLTE_PHY_N_SAMPS_PER_SUBFR_1_92MHZ)
            {
                N_rx_samps = LIBLTE_PHY_N_SAMPS_PER_SUBFR_1_92MHZ;
                N_tx_samps = LIBLTE_PHY_N_SAMPS_PER_SUBFR_1_92MHZ;

                err = LTE_FDD_ENB_ERROR_NONE;
            }
            N_rx_sync_samps = N_rx_samps;
        }else{
            err = LTE_FDD_ENB_ERROR_MASTER_CLOCK_FAIL;
        }
    }catch(...){
        // Nothing to do here
    }

    return err;
}
void LTE_fdd_enb_radio_usrp_b2x0::teardown()
{
    uhd::stream_cmd_t cmd = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;
    usrp->issue_stream_cmd(cmd);
}
void LTE_fdd_enb_radio_usrp_b2x0::send(LTE_FDD_ENB_RADIO_TX_BUF_STRUCT *buf,
                                       LTE_FDD_ENB_RADIO_PARAMS_STRUCT *radio_params)
{
    // Setup metadata
    uhd::tx_metadata_t metadata;
    metadata.has_time_spec  = true;
    metadata.start_of_burst = false;
    metadata.end_of_burst   = false;

    // Check current_tti
    if(buf->current_tti != next_tx_current_tti)
    {
        uint16 N_skipped_subfrs  = liblte_phy_sub_from_tti(buf->current_tti, next_tx_current_tti);
        next_tx_ts              += uhd::time_spec_t::from_ticks(N_skipped_subfrs*radio_params->N_samps_per_subfr,
                                                                radio_params->fs);
    }
    next_tx_current_tti = liblte_phy_add_to_tti(buf->current_tti, 1);

#if EXTRA_TX_RADIO_DEBUG
    radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                            LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                            __FILE__,
                                            __LINE__,
                                            "Sending subfr %lld %u",
                                            next_tx_ts.to_ticks(radio_params->fs),
                                            buf->current_tti);
#endif
    uint32 samps_to_send = radio_params->N_samps_per_subfr;
    uint32 idx           = 0;
    while(samps_to_send)
    {
        metadata.time_spec = next_tx_ts;
        for(uint32 i=0; i<N_tx_samps; i++)
            tx_buf[i] = buf->samps[0][idx+i]/complex(50, 0);
        uint32 sent_samps = N_tx_samps;
        if(samps_to_send < N_tx_samps)
            sent_samps = samps_to_send;
#if EXTRA_TX_RADIO_DEBUG
        radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                                LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                __FILE__,
                                                __LINE__,
                                                "Calling send");
#endif
        tx_stream->send(tx_buf, sent_samps, metadata);
#if EXTRA_TX_RADIO_DEBUG
        radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                                LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                __FILE__,
                                                __LINE__,
                                                "Done with send");
#endif
        idx           += sent_samps;
        samps_to_send -= sent_samps;
        next_tx_ts    += uhd::time_spec_t::from_ticks(sent_samps,
                                                      radio_params->fs);
    }
}
void LTE_fdd_enb_radio_usrp_b2x0::init(LTE_FDD_ENB_RADIO_PARAMS_STRUCT *radio_params)
{
    if(!radio_params->init_needed)
        return;

    // Setup time specs
    next_tx_ts        = uhd::time_spec_t::from_ticks(radio_params->samp_rate,
                                                     radio_params->samp_rate); // 1 second to make sure everything is setup
    next_rx_ts        = next_tx_ts;
    next_rx_ts       -= uhd::time_spec_t::from_ticks(radio_params->N_samps_per_subfr*2,
                                                     radio_params->samp_rate); // Retard RX by 2 subframes
    next_rx_subfr_ts  = next_rx_ts;

    // Reset USRP time
    usrp->set_time_now(uhd::time_spec_t::from_ticks(0, radio_params->samp_rate));

    // Signal PHY to generate first subframe
    radio_params->phy->radio_interface(&radio_params->tx_radio_buf[1]);

    // Start streaming
    uhd::stream_cmd_t cmd = uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS;
    cmd.stream_now        = true;
    usrp->issue_stream_cmd(cmd);

    radio_params->init_needed = false;
}
inline void LTE_fdd_enb_radio_usrp_b2x0::rx_sync(LTE_FDD_ENB_RADIO_PARAMS_STRUCT *radio_params)
{
    int64 N_samps       = rx_stream->recv(rx_buf, N_rx_sync_samps, metadata);
    int64 md_ticks      = metadata.time_spec.to_ticks(radio_params->samp_rate);
    int64 next_rx_ticks = next_rx_ts.to_ticks(radio_params->samp_rate);

    // If the next recv() call will start at the expected next receive TS, then we are synced.
    if((md_ticks + N_samps) == next_rx_ticks)
    {
        radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                                LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                __FILE__,
                                                __LINE__,
                                                "RX synced %lld %lld",
                                                md_ticks + N_samps,
                                                next_rx_ticks);
        radio_params->samp_idx  = 0;
        radio_params->rx_synced = true;
        return;
    }

    // If this recv() call returned enough samples to exceed the expected next receive TS,
    // then we need to modify the next receive TS.
    // FIXME: Need to do many things

    // If the next recv() call will return enough samples to exceed the expected next receive
    // TS, then we need to modify the N_rx_sync_samps to align the TS.
    if((md_ticks + N_samps + N_rx_samps) > next_rx_ticks)
    {
        N_rx_sync_samps  = next_rx_ticks - (md_ticks + N_samps);
        radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                                LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                __FILE__,
                                                __LINE__,
                                                "RX modifying N_rx_sync_samps to sync %lld %lld %u",
                                                md_ticks + N_samps + N_rx_samps,
                                                next_rx_ticks,
                                                N_rx_sync_samps);
    }
}
void LTE_fdd_enb_radio_usrp_b2x0::receive(LTE_FDD_ENB_RADIO_PARAMS_STRUCT *radio_params)
{
    if(!radio_params->rx_synced)
        return rx_sync(radio_params);

#if EXTRA_RX_RADIO_DEBUG
        radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                                LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                __FILE__,
                                                __LINE__,
                                                "Calling recv");
#endif
    uint32 N_samps = rx_stream->recv(rx_buf, N_rx_samps, metadata);
#if EXTRA_RX_RADIO_DEBUG
        radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                                LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                __FILE__,
                                                __LINE__,
                                                "Done with recv");
#endif

    // Catch any errors
    if(N_samps == 0)
        return radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                                       LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                       __FILE__,
                                                       __LINE__,
                                                       "RX number of samples error %u",
                                                       (uint32)metadata.error_code);
    if(metadata.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE)
        return radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                                       LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                       __FILE__,
                                                       __LINE__,
                                                       "RX error %u",
                                                       (uint32)metadata.error_code);
    if(N_samps != N_rx_samps)
        radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                                LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                __FILE__,
                                                __LINE__,
                                                "RX packet size issue %u %u",
                                                N_samps,
                                                N_rx_samps);
        
    uint32 next_rx_ticks = next_rx_ts.to_ticks(radio_params->samp_rate);
    uint32 md_ticks      = metadata.time_spec.to_ticks(radio_params->samp_rate);
    if(next_rx_ticks > md_ticks)
        return radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                                       LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                       __FILE__,
                                                       __LINE__,
                                                       "RX underrun ?!? %lld %lld",
                                                       md_ticks,
                                                       next_rx_ticks);
    if(next_rx_ticks < md_ticks)
    {
        radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                                LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                __FILE__,
                                                __LINE__,
                                                "RX overrun %lld %lld",
                                                md_ticks,
                                                next_rx_ticks);

        // Determine how many subframes we are going to drop
        uint32 N_subfrs_dropped = ((md_ticks - next_rx_ticks)/radio_params->N_samps_per_subfr) + 10;

        // Jump the rx_current_tti
        radio_params->rx_current_tti = liblte_phy_add_to_tti(radio_params->rx_current_tti,
                                                             N_subfrs_dropped);

        // Align the samples coming from the radio
        radio_params->rx_synced  = false;
        next_rx_subfr_ts        += uhd::time_spec_t::from_ticks(N_subfrs_dropped*radio_params->N_samps_per_subfr,
                                                                radio_params->samp_rate);
        next_rx_ts               = next_rx_subfr_ts;
        N_rx_sync_samps          = N_rx_samps;
        return;
    }

    next_rx_ts += uhd::time_spec_t::from_ticks(N_samps, radio_params->samp_rate);
    if((radio_params->samp_idx + N_samps) > radio_params->N_samps_per_subfr)
        return radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                                       LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                       __FILE__,
                                                       __LINE__,
                                                       "MISALIGNED RX %lld %lld",
                                                       radio_params->samp_idx + N_samps,
                                                       radio_params->N_samps_per_subfr);

    for(uint32 i=0; i<N_samps; i++)
        radio_params->rx_radio_buf[radio_params->buf_idx].samps[0][radio_params->samp_idx+i] = rx_buf[i];
    radio_params->samp_idx += N_samps;

    if(radio_params->samp_idx == radio_params->N_samps_per_subfr)
    {
#if EXTRA_RX_RADIO_DEBUG
        radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                                LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                __FILE__,
                                                __LINE__,
                                                "Receiving subfr %lld %u",
                                                next_rx_subfr_ts.to_ticks(radio_params->samp_rate),
                                                radio_params->rx_current_tti);
#endif
        radio_params->rx_radio_buf[radio_params->buf_idx].current_tti = radio_params->rx_current_tti;
        radio_params->phy->radio_interface(&radio_params->tx_radio_buf[radio_params->buf_idx],
                                           &radio_params->rx_radio_buf[radio_params->buf_idx]);
        radio_params->buf_idx         = (radio_params->buf_idx + 1) % 2;
        radio_params->rx_current_tti  = liblte_phy_add_to_tti(radio_params->rx_current_tti, 1);
        radio_params->samp_idx        = 0;
        next_rx_subfr_ts             += uhd::time_spec_t::from_ticks(radio_params->N_samps_per_subfr,
                                                                     radio_params->samp_rate);
    }
}

/****************************************/
/*    BladeRF Constructor/Destructor    */
/****************************************/
LTE_fdd_enb_radio_bladerf::LTE_fdd_enb_radio_bladerf() :
    bladerf{NULL}, first_tx_sample{true}
{
    memset(&metadata_tx, 0, sizeof(metadata_tx));
}
LTE_fdd_enb_radio_bladerf::~LTE_fdd_enb_radio_bladerf()
{
}
void LTE_fdd_enb_radio_bladerf::set_interface(LTE_fdd_enb_interface *iface)
{
    interface = iface;
}

/*********************************/
/*    BladeRF Radio Functions    */
/*********************************/
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio_bladerf::setup(uint32 idx,
                                                        uint32 bw,
                                                        int16  dl_earfcn,
                                                        int16  ul_earfcn,
                                                        uint8  N_ant,
                                                        uint32 samp_rate,
                                                        uint32 N_samps_per_subfr)
{
    // Only supporting N_ant=1
    if(1 != N_ant)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Not supported N_ant=%u",
                                  N_ant);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Determine the bladerf index
    uint32 bladerf_idx = idx - find_usrps() - 1;
    if(bladerf_idx >= find_bladerfs())
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Incorrect bladerf index %u",
                                  bladerf_idx);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Open bladerf device
    struct bladerf_devinfo *devs;
    bladerf_get_device_list(&devs);
    int status = bladerf_open_with_devinfo(&bladerf, &devs[bladerf_idx]);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to open device: %s",
                                  bladerf_strerror(status));
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Set RX frequency
    status = bladerf_set_frequency(bladerf,
                                   BLADERF_MODULE_RX,
                                   liblte_interface_ul_earfcn_to_frequency(ul_earfcn));
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set RX frequency: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Set RX sample rate
    status = bladerf_set_sample_rate(bladerf,
                                     BLADERF_MODULE_RX,
                                     samp_rate,
                                     NULL);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set RX sample rate: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Set RX bandwidth
    status = bladerf_set_bandwidth(bladerf,
                                   BLADERF_MODULE_RX,
                                   bw,
                                   NULL);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set RX bandwidth: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Set LNA gain
    // FIXME: rx_gain
    status = bladerf_set_lna_gain(bladerf,
                                  BLADERF_LNA_GAIN_MID);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set LNA gain: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Set RX VGA1 gain
    // FIXME: rx_gain
    status = bladerf_set_rxvga1(bladerf,
                                BLADERF_RXVGA1_GAIN_MIN);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set RX VGA1 gain: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Set RX VGA2 gain
    // FIXME: rx_gain
    status = bladerf_set_rxvga2(bladerf,
                                BLADERF_RXVGA2_GAIN_MIN);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set RX VGA2 gain: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Set TX frequency
    status = bladerf_set_frequency(bladerf,
                                   BLADERF_MODULE_TX,
                                   liblte_interface_dl_earfcn_to_frequency(dl_earfcn));
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set TX frequency: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Set TX sample rate
    status = bladerf_set_sample_rate(bladerf,
                                     BLADERF_MODULE_TX,
                                     samp_rate,
                                     NULL);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set TX sample rate: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Set TX bandwidth
    status = bladerf_set_bandwidth(bladerf,
                                   BLADERF_MODULE_TX,
                                   bw,
                                   NULL);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set TX bandwidth: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Set TX VGA1 gain
    // FIXME: tx_gain
    status = bladerf_set_txvga1(bladerf,
                                BLADERF_TXVGA1_GAIN_MAX);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set TX VGA1 gain: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Set TX VGA2 gain
    // FIXME: tx_gain
    status = bladerf_set_txvga2(bladerf,
                                BLADERF_TXVGA2_GAIN_MAX - 1);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set TX VGA2 gain: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Setup sync TX
    uint32 buffer_size = 1024;
    if(0 == (N_samps_per_subfr % 1024))
        buffer_size = N_samps_per_subfr;
    status = bladerf_sync_config(bladerf,
                                 BLADERF_TX_X1,
                                 BLADERF_FORMAT_SC16_Q11_META,
                                 BLADERF_NUM_BUFFERS,
                                 buffer_size,
                                 BLADERF_NUM_TRANSFERS,
                                 BLADERF_TIMEOUT_MS);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set TX sync config: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Setup sync RX
    status = bladerf_sync_config(bladerf,
                                 BLADERF_RX_X1,
                                 BLADERF_FORMAT_SC16_Q11_META,
                                 BLADERF_NUM_BUFFERS,
                                 buffer_size,
                                 BLADERF_NUM_TRANSFERS,
                                 BLADERF_TIMEOUT_MS);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to set RX sync config: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Enable TX
    status = bladerf_enable_module(bladerf, BLADERF_MODULE_TX, true);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to enable TX module: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    // Enable RX
    status = bladerf_enable_module(bladerf, BLADERF_MODULE_RX, true);
    if(0 != status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "Failed to enable RX module: %s",
                                  bladerf_strerror(status));
        bladerf_close(bladerf);
        return LTE_FDD_ENB_ERROR_CANT_START;
    }

    return LTE_FDD_ENB_ERROR_NONE;
}
void LTE_fdd_enb_radio_bladerf::teardown()
{
    if(NULL != bladerf)
        bladerf_close(bladerf);
}
void LTE_fdd_enb_radio_bladerf::send(LTE_FDD_ENB_RADIO_TX_BUF_STRUCT *buf,
                                     LTE_FDD_ENB_RADIO_PARAMS_STRUCT *radio_params)
{
    // Check current_tti
    if(buf->current_tti != next_tx_current_tti)
    {
        uint16 N_skipped_subfrs = liblte_phy_sub_from_tti(buf->current_tti,
                                                          next_tx_current_tti);

        next_tx_ts            += N_skipped_subfrs * radio_params->N_samps_per_subfr;
        next_tx_current_tti    = liblte_phy_add_to_tti(buf->current_tti, 1);
        metadata_tx.flags      = BLADERF_META_FLAG_TX_UPDATE_TIMESTAMP;
        metadata_tx.timestamp  = next_tx_ts;
    }else{
        next_tx_current_tti = liblte_phy_add_to_tti(next_tx_current_tti, 1);
        metadata_tx.flags   = 0;
    }

    uint32 samps_to_send = radio_params->N_samps_per_subfr;
    for(uint32 i=0; i<samps_to_send; i++)
    {
        tx_buf[(i*2)  ] = (int16_t)(buf->samps[0][i].real() * 40.0);
        tx_buf[(i*2)+1] = (int16_t)(buf->samps[0][i].imag() * 40.0);
    }

    if(first_tx_sample)
    {
        metadata_tx.flags     = BLADERF_META_FLAG_TX_BURST_START;
        metadata_tx.timestamp = next_tx_ts;
        first_tx_sample       = false;
    }

    // TX samples
    int status = bladerf_sync_tx(bladerf, tx_buf, samps_to_send, &metadata_tx, 1000);
    if(BLADERF_ERR_TIME_PAST == status)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "TX failed: BLADERF_ERR_TIME_PAST");
    }else if(0 != status){
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "TX failed: %s",
                                  bladerf_strerror(status));
    }else if(BLADERF_META_STATUS_UNDERRUN & metadata_tx.status){
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                  __FILE__,
                                  __LINE__,
                                  "TX failed: BLADERF_META_STATUS_UNDERRUN");
    }

    next_tx_ts += samps_to_send;
}
void LTE_fdd_enb_radio_bladerf::init(LTE_FDD_ENB_RADIO_PARAMS_STRUCT *radio_params)
{
    if(!radio_params->init_needed)
        return;

    // Assume RX_timestamp and TX_timestamp difference is 0
    bladerf_get_timestamp(bladerf, BLADERF_RX, (uint64_t*)&rx_ts);
    next_tx_ts            = rx_ts + radio_params->samp_rate; // 1 second to make sure everything is setup
    metadata_rx.flags     = 0;
    metadata_rx.timestamp = next_tx_ts - (radio_params->N_samps_per_subfr*2); // Retard RX by 2 subframes

    // Signal PHY to generate first subframe
    radio_params->phy->radio_interface(&radio_params->tx_radio_buf[1]);

    radio_params->init_needed = false;
}
void LTE_fdd_enb_radio_bladerf::receive(LTE_FDD_ENB_RADIO_PARAMS_STRUCT *radio_params)
{
    metadata_rx.flags = 0; // Use timestamps

    // RX
    int status = bladerf_sync_rx(bladerf, rx_buf, radio_params->N_samps_per_subfr, &metadata_rx, 1000);
    if(0 != status)
    {
        radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                                LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                __FILE__,
                                                __LINE__,
                                                "RX failed: %s",
                                                bladerf_strerror(status));
    }else if(BLADERF_META_STATUS_OVERRUN & metadata_rx.status){
        radio_params->interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                                LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                __FILE__,
                                                __LINE__,
                                                "RX failed: BLADERF_META_STATUS_OVERRUN");

        // Determine how many subframes we are going to drop
        uint32 N_subfrs_dropped = 10;

        // Jump the rx_current_tti and timestamp
        radio_params->rx_current_tti  = liblte_phy_add_to_tti(radio_params->rx_current_tti,
                                                              N_subfrs_dropped);
        metadata_rx.timestamp        += N_subfrs_dropped * radio_params->N_samps_per_subfr;

        // FIXME: This doesn't recover from the overrun
    }else{
        for(uint32 i=0; i<radio_params->N_samps_per_subfr; i++)
            radio_params->rx_radio_buf[radio_params->buf_idx].samps[0][i] = complex(rx_buf[i*2] / 40.0, rx_buf[i*2+1] / 40.0);
        metadata_rx.timestamp                                         += radio_params->N_samps_per_subfr;
        radio_params->rx_radio_buf[radio_params->buf_idx].current_tti  = radio_params->rx_current_tti;
        radio_params->phy->radio_interface(&radio_params->tx_radio_buf[radio_params->buf_idx],
                                           &radio_params->rx_radio_buf[radio_params->buf_idx]);
        radio_params->buf_idx        = (radio_params->buf_idx + 1) % 2;
        radio_params->rx_current_tti = liblte_phy_add_to_tti(radio_params->rx_current_tti, 1);
    }
}

/********************************/
/*    Constructor/Destructor    */
/********************************/
LTE_fdd_enb_radio::LTE_fdd_enb_radio(LTE_fdd_enb_interface *iface, LTE_fdd_enb_phy *_phy) :
    started{false}, interface{iface}, phy{_phy}, clock_source{"internal"}, tx_gain{0},
    rx_gain{0}
{
    bladerf.set_interface(interface);

    // Setup generic radios
    available_radios.num_radios = 0;
    get_available_radios();

    // Setup radio thread
    get_radio_sample_rate();
}
LTE_fdd_enb_radio::~LTE_fdd_enb_radio()
{
    stop();
}

/********************/
/*    Start/Stop    */
/********************/
bool LTE_fdd_enb_radio::is_started()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    return started;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio::start()
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_CANT_START;

    start_mutex.lock();
    if(false == started)
    {
        // Get the DL and UL EARFCNs
        uint16 dl_earfcn = interface->get_dl_earfcn();
        uint16 ul_earfcn = interface->get_ul_earfcn();

        // Get the number of TX antennas
        uint8 N_ant = interface->get_n_ant();
        radio_params.N_ant = N_ant;

        // Get the bandwidth
        uint32 bandwidth = 0;
        switch(interface->get_bandwidth())
        {
        case MasterInformationBlock::k_dl_Bandwidth_n100:
            bandwidth = 20000000;
            break;
        case MasterInformationBlock::k_dl_Bandwidth_n75:
            bandwidth = 15000000;
            break;
        case MasterInformationBlock::k_dl_Bandwidth_n50:
            bandwidth = 10000000;
            break;
        case MasterInformationBlock::k_dl_Bandwidth_n25:
            bandwidth = 5000000;
            break;
        case MasterInformationBlock::k_dl_Bandwidth_n15:
            bandwidth = 3000000;
            break;
        case MasterInformationBlock::k_dl_Bandwidth_n6:
            bandwidth = 1400000;
            break;
        }

        // Setup the appropriate radio
        started = true;
        start_mutex.unlock();
        switch(get_selected_radio_type())
        {
        case LTE_FDD_ENB_RADIO_TYPE_NO_RF:
            err = no_rf.setup();
            if(LTE_FDD_ENB_ERROR_NONE != err)
            {
                started = false;
                return err;
            }
            break;
        case LTE_FDD_ENB_RADIO_TYPE_USRP_B2X0:
            err = usrp_b2x0.setup(selected_radio_idx,
                                  bandwidth,
                                  dl_earfcn,
                                  ul_earfcn,
                                  &clock_source,
                                  get_radio_sample_rate(),
                                  tx_gain,
                                  rx_gain);
            if(LTE_FDD_ENB_ERROR_NONE != err)
            {
                started = false;
                return err;
            }
            break;
        case LTE_FDD_ENB_RADIO_TYPE_BLADERF:
            err = bladerf.setup(selected_radio_idx,
                                bandwidth,
                                dl_earfcn,
                                ul_earfcn,
                                N_ant,
                                get_radio_sample_rate(),
                                radio_params.N_samps_per_subfr);
            if(LTE_FDD_ENB_ERROR_NONE != err)
            {
                started = false;
                return err;
            }
            break;
        default:
            started = false;
            return LTE_FDD_ENB_ERROR_OUT_OF_BOUNDS;
            break;
        }

        pthread_create(&radio_thread, NULL, &radio_thread_func, this);
    }else{
        start_mutex.unlock();
    }

    return err;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio::stop()
{
    LTE_FDD_ENB_ERROR_ENUM err = LTE_FDD_ENB_ERROR_CANT_STOP;

    start_mutex.lock();
    if(started)
    {
        started = false;
        start_mutex.unlock();
        switch(get_selected_radio_type())
        {
        case LTE_FDD_ENB_RADIO_TYPE_NO_RF:
            no_rf.teardown();
            break;
        case LTE_FDD_ENB_RADIO_TYPE_USRP_B2X0:
            usrp_b2x0.teardown();
            break;
        case LTE_FDD_ENB_RADIO_TYPE_BLADERF:
            bladerf.teardown();
            break;
        default:
            err = LTE_FDD_ENB_ERROR_OUT_OF_BOUNDS;
            break;
        }
        sleep(1);
        pthread_cancel(radio_thread);
        pthread_join(radio_thread, NULL);
        err = LTE_FDD_ENB_ERROR_NONE;
    }else{
        start_mutex.unlock();
    }

    return err;
}

/****************************/
/*    External Interface    */
/****************************/
std::string LTE_fdd_enb_radio::get_available_radios_string()
{
    LTE_FDD_ENB_AVAILABLE_RADIOS_STRUCT radios = get_available_radios();
    std::string str;
    for(uint32 i=0; i<radios.num_radios; i++)
        str += std::to_string(i) + ": " + radios.radio[i].name + ", ";
    if(str.length() != 0)
        return str.substr(0, str.length()-2);
    return str;
}
LTE_FDD_ENB_AVAILABLE_RADIOS_STRUCT LTE_fdd_enb_radio::get_available_radios()
{
    uint32 orig_num_radios = available_radios.num_radios;
    available_radios.num_radios = 0;

    // No RF
    available_radios.radio[available_radios.num_radios].name   = "no_rf";
    available_radios.radio[available_radios.num_radios++].type = LTE_FDD_ENB_RADIO_TYPE_NO_RF;

    // USRP devices
    find_usrps(&available_radios);

    // bladerf devices
    find_bladerfs(&available_radios);

    // Reset to sane default
    if(orig_num_radios != available_radios.num_radios)
    {
        selected_radio_idx = 1;
        if(1 == available_radios.num_radios)
            selected_radio_idx = 0;
        selected_radio_type = available_radios.radio[selected_radio_idx].type;
    }

    return available_radios;
}
LTE_FDD_ENB_RADIO_STRUCT LTE_fdd_enb_radio::get_selected_radio()
{
    uint32 num_usrps    = find_usrps();
    uint32 num_bladerfs = find_bladerfs();

    if(available_radios.num_radios != (num_usrps + num_bladerfs + 1))
        get_available_radios();

    return available_radios.radio[selected_radio_idx];
}
uint32 LTE_fdd_enb_radio::get_selected_radio_idx()
{
    uint32 num_usrps    = find_usrps();
    uint32 num_bladerfs = find_bladerfs();

    if(available_radios.num_radios != (num_usrps + num_bladerfs + 1))
        get_available_radios();

    return selected_radio_idx;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio::set_selected_radio_idx(std::string idx)
{
    int64 idx_value;
    if(to_number(idx, idx_value, 0, 100))
        return LTE_FDD_ENB_ERROR_OUT_OF_BOUNDS;
    return set_selected_radio_idx((uint32)idx_value);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio::set_selected_radio_idx(uint32 idx)
{
    uint32                 num_usrps    = find_usrps();
    uint32                 num_bladerfs = find_bladerfs();
    LTE_FDD_ENB_ERROR_ENUM err          = LTE_FDD_ENB_ERROR_OUT_OF_BOUNDS;

    if(available_radios.num_radios != (num_usrps + num_bladerfs + 1))
        get_available_radios();

    if(idx < available_radios.num_radios)
    {
        selected_radio_idx  = idx;
        selected_radio_type = available_radios.radio[selected_radio_idx].type;
        err                 = LTE_FDD_ENB_ERROR_NONE;
    }

    return err;
}
LTE_FDD_ENB_RADIO_TYPE_ENUM LTE_fdd_enb_radio::get_selected_radio_type()
{
    uint32 num_usrps    = find_usrps();
    uint32 num_bladerfs = find_bladerfs();

    if(available_radios.num_radios != (num_usrps + num_bladerfs + 1))
        get_available_radios();

    return available_radios.radio[selected_radio_idx].type;
}
uint32 LTE_fdd_enb_radio::get_tx_gain()
{
    return tx_gain;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio::set_tx_gain(std::string gain)
{
    int64 gain_value;
    if(to_number(gain, gain_value, 0, 1000))
        return LTE_FDD_ENB_ERROR_OUT_OF_BOUNDS;
    return set_tx_gain((uint32)gain_value);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio::set_tx_gain(uint32 gain)
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        return LTE_FDD_ENB_ERROR_OUT_OF_BOUNDS;

    tx_gain = gain;
    return LTE_FDD_ENB_ERROR_NONE;
}
uint32 LTE_fdd_enb_radio::get_rx_gain()
{
    return rx_gain;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio::set_rx_gain(std::string gain)
{
    int64 gain_value;
    if(to_number(gain, gain_value, 0, 1000))
        return LTE_FDD_ENB_ERROR_OUT_OF_BOUNDS;
    return set_rx_gain((uint32)gain_value);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio::set_rx_gain(uint32 gain)
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        return LTE_FDD_ENB_ERROR_OUT_OF_BOUNDS;

    rx_gain = gain;
    return LTE_FDD_ENB_ERROR_NONE;
}
std::string LTE_fdd_enb_radio::get_clock_source()
{
    return clock_source;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_radio::set_clock_source(std::string source)
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        return LTE_FDD_ENB_ERROR_OUT_OF_BOUNDS;

    if("internal" != source && "external" != source)
        return LTE_FDD_ENB_ERROR_OUT_OF_BOUNDS;

    clock_source = source;
    return LTE_FDD_ENB_ERROR_NONE;
}
uint32 LTE_fdd_enb_radio::get_phy_sample_rate()
{
    if(started)
        return radio_params.fs;

    MasterInformationBlock::dl_Bandwidth_Enum dl_bw = interface->get_bandwidth();
    switch(dl_bw)
    {
    case MasterInformationBlock::k_dl_Bandwidth_n100:
        // Intentional fall-thru
    case MasterInformationBlock::k_dl_Bandwidth_n75:
        radio_params.fs                = 30720000;
        radio_params.N_samps_per_subfr = LIBLTE_PHY_N_SAMPS_PER_SUBFR_30_72MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n50:
        radio_params.fs                = 15360000;
        radio_params.N_samps_per_subfr = LIBLTE_PHY_N_SAMPS_PER_SUBFR_15_36MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n25:
        radio_params.fs                = 7680000;
        radio_params.N_samps_per_subfr = LIBLTE_PHY_N_SAMPS_PER_SUBFR_7_68MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n15:
        radio_params.fs                = 3840000;
        radio_params.N_samps_per_subfr = LIBLTE_PHY_N_SAMPS_PER_SUBFR_3_84MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n6:
        radio_params.fs                = 1920000;
        radio_params.N_samps_per_subfr = LIBLTE_PHY_N_SAMPS_PER_SUBFR_1_92MHZ;
        break;
    }

    return radio_params.fs;
}
uint32 LTE_fdd_enb_radio::get_radio_sample_rate()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(!started)
        radio_params.fs = get_phy_sample_rate();

    return radio_params.fs;
}
void LTE_fdd_enb_radio::send(LTE_FDD_ENB_RADIO_TX_BUF_STRUCT *buf)
{
    switch(selected_radio_type)
    {
    case LTE_FDD_ENB_RADIO_TYPE_NO_RF:
        no_rf.send();
        break;
    case LTE_FDD_ENB_RADIO_TYPE_USRP_B2X0:
        usrp_b2x0.send(buf, &radio_params);
        break;
    case LTE_FDD_ENB_RADIO_TYPE_BLADERF:
        bladerf.send(buf, &radio_params);
        break;
    default:
        radio_params.interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                               LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                               __FILE__,
                                               __LINE__,
                                               "Invalid radio type %u",
                                               selected_radio_type);
        break;
    }
}
pthread_t LTE_fdd_enb_radio::get_radio_thread()
{
    return radio_thread;
}

/************************/
/*    Generic Radios    */
/************************/
void* LTE_fdd_enb_radio::radio_thread_func(void *inputs)
{
    // Setup radio params
    LTE_fdd_enb_radio *radio           = (LTE_fdd_enb_radio*)inputs;
    radio->radio_params.interface      = radio->interface;
    radio->radio_params.phy            = radio->phy;
    radio->radio_params.samp_rate      = radio->radio_params.fs;
    radio->radio_params.buf_idx        = 0;
    radio->radio_params.samp_idx       = 0;
    radio->radio_params.rx_current_tti = liblte_phy_sub_from_tti(0, 2);
    radio->radio_params.init_needed    = true;
    radio->radio_params.rx_synced      = false;

    // Set highest priority
    struct sched_param priority;
    int                sched_policy;
    pthread_getschedparam(radio->radio_thread, &sched_policy, &priority);
    priority.sched_priority = sched_get_priority_max(SCHED_FIFO);
    pthread_setschedparam(radio->radio_thread, SCHED_FIFO, &priority);

    // Set affinity to the last core for PHY/Radio
    cpu_set_t af_mask;
    CPU_ZERO(&af_mask);
    uint32 num_cpus = std::thread::hardware_concurrency();
    CPU_SET(num_cpus-1, &af_mask);
    pthread_setaffinity_np(radio->get_radio_thread(), sizeof(af_mask), &af_mask);

    switch(radio->get_selected_radio_type())
    {
    case LTE_FDD_ENB_RADIO_TYPE_NO_RF:
        radio->no_rf.init(&radio->radio_params);
        while(radio->is_started())
            radio->no_rf.receive(&radio->radio_params);
        break;
    case LTE_FDD_ENB_RADIO_TYPE_USRP_B2X0:
        radio->usrp_b2x0.init(&radio->radio_params);
        while(radio->is_started())
            radio->usrp_b2x0.receive(&radio->radio_params);
        break;
    case LTE_FDD_ENB_RADIO_TYPE_BLADERF:
        radio->bladerf.init(&radio->radio_params);
        while(radio->is_started())
            radio->bladerf.receive(&radio->radio_params);
        break;
    default:
        radio->radio_params.interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                                      LTE_FDD_ENB_DEBUG_LEVEL_RADIO,
                                                      __FILE__,
                                                      __LINE__,
                                                      "Invalid radio type");
        break;
    }

    return NULL;
}
