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

#ifndef _MM_H
#define _MM_H

#include <kvnix/mm/const.h>
#include <kvnix/mm/types.h>

/**
 * @file
 *
 * Memory manager function.
 * 
 * <p>The memory that can be allocated is represented by memory_area_t. 
 * This is divided in memory slots (memory_slot_t), which can be free or allocated.</p>
 * 
 * <p>For exemple, suppose that the sistem initializes with a free memory area from 0x0000 to
 * 0x0400 (1 kb). We know that:
 * <br/>1. The memory area contains one element on its free slot list;
 * <br/>2. This slot has the attributes begin=0x0000 and size=0x0400;
 * <br/>3. The memory position 0x0000 constains an instance of list_elem_t (list element), which 
 *    is used to find the next free memory slot;
 * <br/>4. The memory position 0x0000+sizeof(list_elem_t) contains an instance of memory_slot;
 * <br/>5. The attribute value of the list element is the memory slot descriptor.</p>
 *
 * <p>Now, imagine that we requested a block of 500 bytes. The memory manager will:
 * <br/>1. Split the memory slot in two parts: from 0x000 to 0x01F4(500) and from 0x01F5 to 0x0400;
 * <br/>2. Define the first memory slot as allocated
 * <br/>3. Remove the allocated memory slot from the free list;
 * <br/>4. Add the allocated memory slot to the allocated list.</p>
 * 
 * <p>When the function free_allocated_memory() is called, the memory managet will:
 * <br/>1. Define the memory slot as free;
 * <br/>2. Remove the free memory slot from the allocated list;
 * <br/>3. Add the memory slot to the free list;
 * <br/>4. Merge this memory slot with the other free slot.</p>
 *
 * @author Victor V. Serta
 */

/**
 * Returns the begin of the memory slot header.
 *
 * @param slot
 * @return begin of the memory slot header
 */
#define get_memory_slot_header_begin(slot)          \
   ((void *) (((size_t) slot) - sizeof(list_elem_t)))
 
/**
 * Returns the end of the memory slot header.
 *
 * @param slot
 * @return end of the memory slot header
 */
#define get_memory_slot_header_end(slot)            \
    ((void *)(((size_t) slot) + sizeof(memory_slot_t)))
 
/**
 * Returns the begin of the memory slot.
 *
 * @param slot
 * @return end of the memory slot
 */
#define get_memory_slot_end(slot)                      \
    ((void *) (((size_t) slot->begin) + slot->size - 1))

/**
 * Initializes a new memory area.
 *
 * @param begin memory area begin
 * @param size memory area size
 * @return memory area representation
 */
memory_area_t * init_memory_area(void *begin, size_t size);

/**
 * Adds a free slot to a memory area.
 * 
 * @param memory_area memory area
 * @param begin free memory begin
 * @param size free memory size
 * @return new memory slot or NULL 
 */
memory_slot_t * add_free_slot(memory_area_t *memory_area, void *begin, size_t size);

/**
 * Allocates a memory memory slot.
 *
 * @param memory_area memory area
 * @param size memory size needed
 * @return allocated memory slot
 */
memory_slot_t * allocate_memory_slot(memory_area_t *memory_area, size_t size);

/**
 * Frees an allocated memory slot.
 *
 * @param memory_area memory area
 * @param begin memory slot begin
 * @return free memory slot
 */
memory_slot_t * free_memory_slot(memory_area_t *memory_area, void *begin);

/**
 * Reallocated an allocated memory slot.
 *
 * @param memory_area memory area
 * @param begin memory slot begin
 * @param new_size new slot size
 * @return reallocated memory slot
 */
memory_slot_t * reallocate_memory_slot(memory_area_t *memory_area, void *begin, size_t new_size);
 
/**
 * Prints the slots from a slot list.
 * This function can be used to get debug informations.
 *
 * @param slot_list slot list
 */
void print_slots(list_t *slot_list);
 
/**
 * Prints the memory area.
 * This function can be used to get debug informations.
 *
 * @param slot_list slot list
 */
void print_memory_area(memory_area_t *memory_area);

/**
 * Returns the free space.
 * 
 * @return free space
 */
PUBLIC int get_free_space(memory_area_t *memory_area);

#endif
