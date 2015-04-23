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
 * Global constants used by the system.
 * It includes the contants declared in "code_const.h".
 *
 * @author Victor V. Serta
 * @author Klystofer Ortega
 */

#ifndef _CONST_H
#define _CONST_H

#include <util/code_const.h>

/**
 * Begin of the heap space.
 */
#define KERNEL_HEAP_BEGIN 0x7E00

/**
 * Size of the heap space.
 */
#define KERNEL_HEAP_SIZE 20000

#endif
