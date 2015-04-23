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
 * This file constains boolean constantes e type.
 * This can be used instead of stdbool.h from libc.
 */

#ifndef _SYS_BOOL_H
#define _SYS_BOOL_H

#define true 1              /**< The "true" boolean value. */
#define false 0             /**< The "false" boolean value. */ 

/**
 * Boolean type.
 */
typedef short bool; 
 
#endif
