/*******************************************************************************

    Copyright 2014, 2021 Ben Wojtowicz

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

    File: liblte_common.cc

    Description: Contains all the implementations for the LTE common library.

    Revision History
    ----------    -------------    --------------------------------------------
    08/03/2014    Ben Wojtowicz    Created file.
    11/29/2014    Ben Wojtowicz    Added liblte prefix to value_2_bits and
                                   bits_2_value.
    02/14/2021    Ben Wojtowicz    Massive reformat and added a full stack
                                   message class.

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
                              CLASS IMPLEMENTATIONS
*******************************************************************************/

liblte_full_stack_message::liblte_full_stack_message()
{
    mme.reserve(500);
    rrc.reserve(2000);
    gw.reserve(5000);
    pdcp.reserve(5000);
    mac.reserve(75376);
}
liblte_full_stack_message::~liblte_full_stack_message()
{
}

/*******************************************************************************
                              FUNCTIONS
*******************************************************************************/

/*********************************************************************
    Name: liblte_value_2_bits

    Description: Converts a value to a bit string
*********************************************************************/
void liblte_value_2_bits(uint32   value,
                         uint8  **bits,
                         uint32   N_bits)
{
    for(uint32 i=0; i<N_bits; i++)
        (*bits)[i] = (value >> (N_bits-i-1)) & 0x1;
    *bits += N_bits;
}

/*********************************************************************
    Name: liblte_bits_2_value

    Description: Converts a bit string to a value
*********************************************************************/
uint32 liblte_bits_2_value(uint8  **bits,
                           uint32   N_bits)
{
    uint32 value = 0;

    for(uint32 i=0; i<N_bits; i++)
        value |= (*bits)[i] << (N_bits-i-1);
    *bits += N_bits;

    return value;
}
