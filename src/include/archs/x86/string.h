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
 * x86 routines used to manipulate strings.
 *
 * @author Victor V. Serta
 */

#ifndef _X86_STRING_H
#define _X86_STRING_H

/**
 * Copies a memory region to another.
 *
 * @param to to
 * @param from from
 * @param size size
 */
#define BYTE_COPY(to, from, size)                       \
     __asm__ __volatile__                               \
            ("cld\n\t"                                  \
             "rep\n\t"                                  \
             "movsb"                                    \
            :                                           \
            :"D" (to), "S" (from), "c" (size)           \
            :"memory"                                   \
            )                                           \

/**
 * Sets a character to a memory region.
 *
 * @param block memory block
 * @param c character
 * @param size block size
 */
#define BYTE_SET(block, c, size)                        \
     __asm__ __volatile__                               \
            ("cld\n\t"                                  \
             "rep\n\t"                                  \
             "stosb"                                    \
            :                                           \
            :"D" (block), "a" (c), "c" (size)           \
            :"memory"                                   \
            )                                           \
 

#endif
