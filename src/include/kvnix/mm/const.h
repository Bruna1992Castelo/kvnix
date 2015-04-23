/* Copyright (C) 2009 Klystofer Ortega, Victor Villela Serta
   This file is part of Kvnix.

   Kvnix is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as 
   published by the Free Software Foundation, either version 3 of 
   the License, or (at your option) any later version.

   Kvnix is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public 
   License along with Kvnix. If not, see <http://www.gnu.org/licenses/>. 
*/

#ifndef _MM_CONST_H
#define _MM_CONST_H

#include <kvnix/const.h>
#include <kvnix/mm/types.h>

/**
 * @file
 *
 * Memory manager constants.
 *
 * @author Victor V. Serta
 */ 

/**
 * The magic number that defines a memory slot.
 */
#define MEMORY_SLOT_MAGIC_NUMBER 0xFC

/**
 * The slot header size.
 * It is the add of memory slot size and the list element.
 */
#define SLOT_HEADER_SIZE (sizeof(memory_slot_t) + sizeof(list_elem_t)) 

/**
 * The minimum size of a memoty slot.
 */
#define SLOT_MIN_SIZE SLOT_HEADER_SIZE + (sizeof(char) * 5)


/**
 * 00000000
 * 
 * bit 0: 0 = free; 1 = allocated
 * bit 7..1: not used yet
 */

/**
 * When the first bit of the slot status is set, the slot is allocated. 
 */
#define ALLOCATED_SLOT_MASK 0x01

#endif
