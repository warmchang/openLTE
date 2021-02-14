/*******************************************************************************

    Copyright 2017, 2021 Ben Wojtowicz

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

    File: liblte_common_tests.cc

    Description: Contains all the tests for the LTE common library.

    Revision History
    ----------    -------------    --------------------------------------------
    07/29/2017    Ben Wojtowicz    Created file.
    02/14/2021    Ben Wojtowicz    Massive reformat.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_common.h"

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

int v2b_single_bit_test()
{
    uint8 bits[32];

    for(uint32 i=0; i<32; i++)
    {
        uint8 *bits_ptr = &bits[0];
        liblte_value_2_bits(1<<i, &bits_ptr, 32);
        for(uint32 j=0; j<32; j++)
            if(!((j == i && bits[32-1-j] == 1) || bits[32-1-j] == 0))
                return -1;
    }

    return 0;
}

int v2b_b2v_random_test()
{
    uint8 bits[32];

    for(uint32 i=0; i<32; i++)
    {
        uint32  value    = rand();
        uint8  *bits_ptr = &bits[0];
        liblte_value_2_bits(value, &bits_ptr, 32);
        bits_ptr = &bits[0];
        if(value != liblte_bits_2_value(&bits_ptr, 32))
            return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    printf("v2b_single_bit_test: ");
    if(0 != v2b_single_bit_test())
        exit(-1);
    printf("pass\n");
    printf("v2b_b2v_random_test: ");
    if(0 != v2b_b2v_random_test())
        exit(-1);
    printf("pass\n");
    exit(0);
}
