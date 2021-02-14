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

    File: liblte_interface_tests.cc

    Description: Contains all the tests for the LTE interface library.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_interface.h"

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
                              FUNCTIONS
*******************************************************************************/

int main(int argc, char *argv[])
{
    uint16 dl_earfcns_to_test[4] = {200,
                                    3200,
                                    8365,
                                    37250};
    uint32 dl_freqs_to_test[4] = {2130000000,
                                  2665000000,
                                  1962500000,
                                  1960000000};
    uint16 ul_earfcns_to_test[4] = {18200,
                                    21200,
                                    26365,
                                    37250};
    uint32 ul_freqs_to_test[4] = {1940000000,
                                  2545000000,
                                  1882500000,
                                  1960000000};

    for(uint32 i=0; i<4; i++)
    {
        printf("dl_earfcn_to_freq test: ");
        uint32 freq = liblte_interface_dl_earfcn_to_frequency(dl_earfcns_to_test[i]);
        if(freq != dl_freqs_to_test[i])
            exit(-1);
        printf("pass\n");
        printf("get_corresponding_ul_earfcn test: ");
        uint16 ul_earfcn = liblte_interface_get_corresponding_ul_earfcn(dl_earfcns_to_test[i]);
        if(ul_earfcn != ul_earfcns_to_test[i])
            exit(-1);
        printf("pass\n");
        printf("ul_earfcn_to_freq test: ");
        freq = liblte_interface_ul_earfcn_to_frequency(ul_earfcn);
        if(freq != ul_freqs_to_test[i])
            exit(-1);
        printf("pass\n");
        printf("get_corresponding_dl_earfcn test: ");
        uint16 dl_earfcn = liblte_interface_get_corresponding_dl_earfcn(ul_earfcn);
        if(dl_earfcn != dl_earfcns_to_test[i])
            exit(-1);
        printf("pass\n");
    }

    exit(0);
}
