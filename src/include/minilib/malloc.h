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
 */

#ifndef _MALLOC_H
#define _MALLOC_H

#include <minilib/stddef.h>
#include <util/code_const.h>

/**
 * Allocate a region of size bytes in a memory.
 *
 * @param size size of region
 *
 * @return pointer to the beginning of region allocated
 */
PUBLIC void * malloc(size_t size);

/**
 * Free an allocated region.
 *
 * @param pointer region to be disposed
 *
 */
PUBLIC void free(void* pointer);

/**
 * Reallocate a region for a new one with size bytes.
 *
 * @oaram pointer old region
 * @param size new size
 *
 * @return pointer for an allocated region
 */
PUBLIC void * realloc(void* pointer, size_t size);

#endif
