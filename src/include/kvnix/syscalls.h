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
 * System Call routines.
 *
 * @author Klystofer Ortega
 */

#ifndef _SYS_CALLS_H
#define _SYS_CALLS_H

#include <sys/types.h>
#include <kvnix/const.h>
#include <ipc/ipc.h>

/* --------------------
 *  I/O System calls
 * --------------------
 */

/**
 * Call an interruption passing message struct.
 *
 * @param syscallnr number of the system call.
 * @return message ipc struct to send/receive parameters.
 */ 
PUBLIC void syscall(int syscallnr, message *msgptr);

/**
 * Opens an existing file or create a new file if it does't exist.
 *
 * @param filename name of the file
 * @return file descriptor (fd)
 */ 
PUBLIC int open(const char *filename);

/**
 * Closes an opened file.
 *
 * @param fd file descriptor
 * @return 0 if successful or -1 if failed
 */
PUBLIC int close(int fd);
 
/**
 * Reads from a file and writes to the buffer.
 *
 * @param fd file descriptor
 * @param buffer data
 * @param nbytes size of data in bytes
 *
 * @return the number of bytes that were read or -1 if failed
 */ 
PUBLIC ssize_t read(int fd, void *buffer, size_t nbytes);
 
/**
 * Writes the buffer to a file.
 *
 * @param fd file descriptor
 * @param buffer data
 * @param nbytes size of data in bytes
 *
 * @return the number of bytes that were written or -1 if failed
 */
PUBLIC ssize_t write(int fd, void *buffer, size_t nbytes);

PUBLIC void load_program(const char *name);

PUBLIC int clone(int (*func)(void *), void *child_stack, size_t child_stack_size, void *arg);

PUBLIC void exit(int exit_code);

PUBLIC int waitpid(int pid);

PUBLIC void sched_yield();

#endif
