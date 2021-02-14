#line 2 "LTE_fdd_enb_main.cc" // Make __FILE__ omit the path
/*******************************************************************************

    Copyright 2013-2014, 2021 Ben Wojtowicz

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

    File: LTE_fdd_enb_main.cc

    Description: Contains all the implementations for the LTE FDD eNodeB main
                 loop.

    Revision History
    ----------    -------------    --------------------------------------------
    11/09/2013    Ben Wojtowicz    Created file
    06/15/2014    Ben Wojtowicz    Omitting path from __FILE__.
    11/01/2014    Ben Wojtowicz    Added config and user file support.
    02/14/2021    Ben Wojtowicz    Massive reformat.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_interface.h"
#include "LTE_fdd_enb_hss.h"

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

int main(int argc, char *argv[])
{
    LTE_fdd_enb_interface *interface = new LTE_fdd_enb_interface();

    interface->start_ports();
    interface->read_cnfg_file();

    printf("*** LTE FDD ENB ***\n");
    printf("Please connect to control port %u\n", LTE_FDD_ENB_CTRL_PORT);

    while(!interface->get_shutdown())
        sleep(1);
}
