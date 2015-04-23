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
 * Types used by Kvnix system.
 *
 * @author Victor V. Serta
 */

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

/* -----------------
 * General types
 * -----------------
 */


#ifndef _SIZE_T
#define _SIZE_T
/** 
 * This represents the sizes of objects. For example, it's the return type of
 * the sizeof operator.
 */ 
typedef unsigned int size_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
/**
 * The signed version of size_t.
 */
typedef int ssize_t;
#endif

/**
 * The type time_t represents a simple time. In Unix systems, it's the number 
 * of seconds since 1 Jan 1970 00:00 GMT.
 */
typedef long time_t;

/**
 * Unsigned 8 bits type.
 */
typedef unsigned char u8_t;

/**
 * Unsigned 16 bits type.
 */
typedef unsigned short u16_t; 

/**
 * Unsigned 16 bits type.
 */
typedef unsigned int u32_t; 
 
/**
 * Signed 8 bits type.
 */
typedef char i8_t;                  

/**
 * Signed 16 bits type.
 */
typedef short i16_t;                

/**
 * Signed 32 bits type.
 */
typedef int i32_t;                  

/* ------------------------------
 *  Types used by p.m.
 * ------------------------------
 */ 

/**
 * Processes identification type.
 */
typedef u16_t pid_t;

/* ------------------------------
 *  Types used in disk and inode
 * ------------------------------
 */

/**
 * Major/Minor number device.
 */
typedef short dev_t;

/**
 * File type and permission bits;
 */
typedef short mode_t;


#endif
