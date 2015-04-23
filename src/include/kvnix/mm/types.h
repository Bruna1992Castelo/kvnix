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

#ifndef _MM_TYPES
#define _MM_TYPES

#include <sys/types.h>
#include <util/list.h>

/**
 * @file
 *
 * Memory manager types.
 *
 * @author Victor V. Serta
 */ 

/**
 * Memory slot.
 * The memory slot represents a block of the memory.
 */
typedef struct memory_slot_t {
    /**
     * Magic number of the memory slot.
     * This is used to check if it is really a memory slot.
     */
    int magic_number;
    
    /**
     * Begin of the memory slot.
     */
    void *begin;

    /**
     * Size of the memory slot.
     */
    size_t size;
    
    /**
     * Status of the memory slot. 
     * 
     * bit 0: 0 = free; 1 = allocated
     * bit 7..1: not used yet
     */
    int status;

    /**
     * Debug message.
     * 
     * This is a debug information to help the developers. When the slot is allocated
     * the message is overriden.
     */
    char *debug_message;
} memory_slot_t;

/**
 * Memory area.
 */
typedef struct memory_area_t {
    list_t *free_slots;         /**< Linked list of the free memory slots. */
    list_t *allocated_slots;    /**< Linked list of the allocated memory slots. */ 
} memory_area_t;

#endif
