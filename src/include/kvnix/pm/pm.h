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

#ifndef _PM_H
#define _PM_H

#include <sys/types.h>
#include <kvnix/pm/types.h>
#include <kvnix/pm/const.h>
#include <kvnix/mm/mm.h>

#include "../commands/shell/progs.h"

/**
 * @file
 *
 * Process manager functions.
 *
 * @author Victor V. Serta
 */ 

/**
 * Loads a program.
 *
 * @param name program name
 */
void do_load_program(const char *name);

/**
 * Creates a nre thread to the current process.
 *
 * @param funct start function
 * @param child_stack child stack
 * @param child_stack_size child stack size
 * @param arg start function parameter
 * @return thread id
 */
int do_clone(int (*func)(void *), void *child_stack, size_t child_stack_size, void *arg);

/**
 * Waits other thread exit.
 *
 * @param pid thread id
 * @return exit code
 */
int do_waitpid(int pid);

/**
 * Exits the current task.
 */
void do_exit(int exit_value);

#endif

