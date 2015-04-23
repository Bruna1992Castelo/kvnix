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
 * Standard library.
 *
 * These routines are used by the system instead of libc to mantain the operating
 * system code more simple.
 */

#ifndef _STDLIB_H
#define _STDLIB_H

#include <minilib/stddef.h>
#include <minilib/malloc.h>
#include <util/code_const.h>

/**
 * Convert an integer value into a string using given radix.
 *
 * @param value integer value
 * @param string allocated memory region to write the number converted
 * @param radix radix
 *
 * @return pointer to the string
 */
PUBLIC char * itoa(int value, char *string, int radix);

#endif
