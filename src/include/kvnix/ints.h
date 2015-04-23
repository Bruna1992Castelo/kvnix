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
 * Routines used to handle with interruption system.
 */

#ifndef _INTS_H_
#define _INTS_H_

#include <kvnix/const.h>

/**
 * Handles all sort of system calls.
 */
PUBLIC void handle_int(unsigned short ax, unsigned short bx, unsigned short ds);

/**
 * Timer Interruptions.
 */
PUBLIC void timer_int();

#endif

