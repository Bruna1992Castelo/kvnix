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
 * Shell is a software used to intereract with Kvnix.
 *
 * @author Victor Villela Serta
 * @author Klystofer Ortega
 */

#ifndef _SHELL_H
#define _SHELL_H

#include <util/code_const.h>

/**
 * Pointer to initialization function.
 */
typedef void init_function(); 

/**
 * Command descriptor
 */
typedef struct command_t {
    char *name;
    init_function *init;
} command_t;

/**
 * Table of commands available.
 */
extern command_t commands_table[];

/**
 * Initializes the shell.
 */
PUBLIC void shell_init();

/**
 * Shows the list of commands and requests a command to execute.
 */
PRIVATE void command_list();

/**
 * Requests a command to execute.
 */
PRIVATE void request_command();

/**
 * Runs a command by name.
 */
PRIVATE void run_command(char *command_name);

#endif
