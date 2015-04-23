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
 * Standard defines
 *
 * @author Victor V. Serta
 *
 */

#ifndef _STDDEF_H
#define _STDDEF_H

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif
 
#ifndef _SSIZE_T
#define _SSIZE_T
typedef long ssize_t;
#endif
 
#undef NULL
#define NULL ((void *)0)              /**< Null value. */

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#endif
