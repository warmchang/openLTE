/*******************************************************************************

    Copyright 2021 Ben Wojtowicz

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

    File: LTE_fdd_dl_fg_main.cc

    Description: Contains all the implementations for the LTE FDD DL File
                 Generator main loop.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_fg_interface.h"

#include "unistd.h"

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
    LTE_fdd_dl_fg_interface *interface = new LTE_fdd_dl_fg_interface();

    printf("*** LTE FDD DL FILE GENERATOR ***\n");
    printf("Please connect to control port %u\n", LTE_FDD_DL_FG_CTRL_PORT);

    while(!interface->get_shutdown())
        sleep(1);
}
