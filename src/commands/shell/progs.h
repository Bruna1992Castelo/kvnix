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
 * Programs structures used by shell.
 *
 * @author Klystofer Ortega
 */

#ifndef _PROGS_H_
#define _PROGS_H_

#include <util/code_const.h>

#define PROGS_BEGIN_POS 0x7C00		/* Begin position of programs in disk */
#define NR_PROGS 		5			/* numbers of programs in disk */

/**
 * Program descriptor
 */
typedef struct image_sect_t {
	char * filename;
	char * alias;
	unsigned long start;
	unsigned int nrsects;
} image_sect_t;

/**
 * Table with programs details.
 */
extern image_sect_t progs_table[];

#endif
