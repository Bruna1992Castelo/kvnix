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
 * String manipulation.
 *
 * These functions are used by the system instead of libc to mantain the operating
 * system code more simple.
 */

#ifndef _STRING_H
#define _STRING_H

#include <minilib/stddef.h>
#include <util/code_const.h>


/**
 * Copies a memory region to another. The parameters to and from can not
 * overlap.
 *
 * @param to data destination
 * @param from data origin
 * @param size data size
 *
 * @return the value of to
 */
PUBLIC void * memcpy(void *restrict to, const void *restrict from, size_t size);

/**
 * Copies the character c to a memory region. 
 *
 * @param block memory block
 * @param c character
 * @param size block size
 *
 * @return the value of block
 */
PUBLIC void * memset(void *block, int c, size_t size);

/**
 * Copies the string beginning in to to the string beginning in from. The 
 * parameters to and from can not overlap. 

 * @param to string destination
 * @param from string origin
 *
 * @return the string to
 */
PUBLIC char * strcpy(char *restrict to, const char *restrict from);

/**
 * Copies size characters from the string from to the string to. The parameters to and 
 * from can not overlap. 
 *
 * @param to string destination
 * @param from string origin
 * @param size characters to be copied
 *
 * @return the string to
 */
PUBLIC char * strncpy(char *restrict to, const char *restrict from, size_t size);
 
/**
 * Concatenates the characters from the string from to the string to. 
 * The parameters to and from can not overlap. 
 *
 * @param to string destination
 * @param from string origin
 *
 * @return the string to
 */
PUBLIC char * strcat(char *restrict to, const char *restrict from);
 
/**
 * Concatenates the characters from the string from to the string to. 
 * The size of string to must be at least size + 1. The parameters to 
 * and from can not overlap. 
 *
 * @param to string destination
 * @param from string origin
 * @param size size of the string after the concatenation
 *
 * @return the string to
 */
PUBLIC char * strncat(char *restrict to, const char *restrict from, size_t size);


/**
 * Returns the length of a string in bytes.
 *
 * @param str null-terminated string
 */
PUBLIC size_t strlen(const char *str);

/**
 * Returns the length of a string in bytes if this length is smaller
 * than maxlen.
 *
 * @param str null-terminated string
 * @param maxlen the maximum lenght of the string
 */
PUBLIC size_t strnlen(const char *str, size_t maxlen);

/**
 * Compare a string with other.
 * @param str1 first string
 * @param str2 second string
 */
PUBLIC int strcmp(const char *str1, const char *str2);


#endif
