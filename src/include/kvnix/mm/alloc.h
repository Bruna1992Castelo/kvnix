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

/**
 * @file
 * 
 * Support functions to handle memory.
 *
 * These funtions are used by the system instead of libc to mantain the operating
 * system code more simple.
 *
 * @author Klystofer Ortega
 */

#ifndef _ALLOC_H
#define _ALLOC_H

#include <kvnix/mm/mm.h>
#include <kvnix/pm/types.h>
#include <minilib/stddef.h>
#include <util/code_const.h>

/**
 * Kernel data process.
 */
extern proc_t system_proc;

/**
 * Current process.
 */
extern proc_t *current_proc; 

/**
 * Current task.
 */
extern task_t *current_task;

/**
 * User Process Heap
 */
#define current_heap (current_proc->memory.heap)
#define current_user_ds (current_task->context.uc_mcontext.mc_ds)

/**
 * Kernel Process Heap
 */
#define kernel_heap (system_proc.memory.heap)

/**
 * Allocate a region of size bytes in the current process heap.
 *
 * @param size size of region
 *
 * @return pointer to the beginning of region allocated
 */
void * do_malloc(size_t size);

/**
 * Free an allocated region.
 *
 * @param pointer region to be disposed
 *
 */
void do_free(void* pointer);

/**
 * Reallocate a region for a new one with other size.
 *
 * @param pointer old region
 * @param size new size
 *
 * @return pointer for an allocated region
 */
void * do_realloc(void* pointer, size_t size);

/**
 * Allocate a region of size bytes in the kernel heap.
 *
 * @param size size of region
 *
 * @return pointer to the beginning of region allocated
 */
void * kmalloc(size_t size);

/**
 * Free an allocated region in kernel heap.
 *
 * @param pointer region to be disposed
 *
 */
void kfree(void* pointer);

/**
 * Reallocate a region in kernel heap for a new one with other size.
 *
 * @param pointer old region
 * @param size new size
 *
 * @return pointer for an allocated region
 */
void * krealloc(void* pointer, size_t size);

#endif
