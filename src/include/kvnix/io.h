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
 * Input/Output functions.
 */

#ifndef _IO_H
#define _IO_H

#include <sys/types.h>
#include <kvnix/const.h>

/* --------------------
 *  I/O System calls
 * --------------------
 */

/**
 * Reads from a file and writes to the buffer.
 *
 * @param fd file descriptor
 * @param buffer data
 * @param nbytes size of data in bytes
 *
 * @return the number of bytes that were read or -1 if failed
 */ 
PUBLIC ssize_t do_read(int fd, void *buffer, size_t nbytes);
 
/**
 * Writes the buffer to a file.
 *
 * @param fd file descriptor
 * @param buffer data
 * @param nbytes size of data in bytes
 *
 * @return the number of bytes that were written or -1 if failed
 */
PUBLIC ssize_t do_write(int fd, void *buffer, size_t nbytes);

#endif
