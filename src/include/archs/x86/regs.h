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
 * Registers Routines.
 */

#ifndef _X86_REGS_H
#define _X86_REGS_H

/**
 * Copy data from one segment to another.
 */
#define BYTE_COPY2(to_seg, to_offset, from_seg, from_offset, size)  \
     __asm__ __volatile__                               			\
            ("pushw %%ds\n"											\
			 "pushw %%es\n"											\
			 "pushw %%ax\n"											\
			 "movw %0, %%ax\n"										\
			 "movw %%ax, %%es\n"									\
			 "movw %1, %%ax\n"										\
			 "movw %%ax, %%ds\n"									\
			 "cld\n\t"                                  			\
             "rep\n\t"                                  			\
             "movsb\n"                                    			\
			 "popw %%ax\n" 											\
			 "popw %%es\n" 											\
			 "popw %%ds\n" 											\
            :                                           			\
            :"m"(to_seg), "m"(from_seg), "D" (to_offset), "S" (from_offset), "c" (size)   \
            :"memory"                                   			\
            )                                           			\

/**
 * Change data segment (DS)
 */
#define CHANGE_DATA_SEGMENT(seg) 	\
	__asm__("pushw %%ax     \n"		\
            "mov %0, %%ax   \n"		\
            "mov %%ax, %%ds \n"		\
            "popw %%ax		\n"		\
            :						\
            : "m"(seg));



#endif
