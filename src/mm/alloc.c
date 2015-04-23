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
__asm__(".code16gcc\n");

#include <kvnix/mm/alloc.h>

#include <kvnix/const.h>
#include <kvnix/mm/mm.h>
#include <minilib/string.h>
#include <minilib/stdlib.h>
#include <minilib/stdio.h>
#include <util/list.h>
#include <archs/x86/regs.h>

PUBLIC void * do_malloc(size_t size) 
{
	unsigned short kernel_ds = 0;
	unsigned short user_ds = current_user_ds;
	memory_area_t *heap = current_heap;
	void *begin;

	CHANGE_DATA_SEGMENT(user_ds);
    memory_slot_t *slot = allocate_memory_slot(heap, size);

	if (slot == NULL)
		begin = NULL;
	else
		begin = slot->begin;

	CHANGE_DATA_SEGMENT(kernel_ds);
    
    return begin;
}

PUBLIC void do_free(void* pointer)
{
	unsigned short kernel_ds = 0;
	unsigned short user_ds = current_user_ds;
	memory_area_t *heap = current_heap;

	CHANGE_DATA_SEGMENT(user_ds);
    free_memory_slot(heap, pointer);
	CHANGE_DATA_SEGMENT(kernel_ds);
}

PUBLIC void * do_realloc(void* pointer, size_t size)
{
	unsigned short kernel_ds = 0;
	unsigned short user_ds = current_user_ds;
	memory_area_t *heap = current_heap;
	void *begin;

	CHANGE_DATA_SEGMENT(user_ds);
    memory_slot_t *slot = reallocate_memory_slot(heap, pointer, size);
 
	if (slot == NULL)
		begin = NULL;
	else
		begin = slot->begin;

	CHANGE_DATA_SEGMENT(kernel_ds);
    
	return begin;
}

PUBLIC void * kmalloc(size_t size) 
{	
    memory_slot_t *slot = allocate_memory_slot(kernel_heap, size);
    
    if (slot == NULL) {
        return NULL;
    }

    return slot->begin;
}

PUBLIC void kfree(void* pointer)
{
    free_memory_slot(kernel_heap, pointer);
}

PUBLIC void * krealloc(void* pointer, size_t size)
{
    memory_slot_t *new_slot = reallocate_memory_slot(kernel_heap, pointer, size);
 
    if (new_slot == NULL) {
        return NULL;
    }

    return new_slot->begin;
}

