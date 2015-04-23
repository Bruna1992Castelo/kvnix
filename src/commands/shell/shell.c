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

__asm__(".code16gcc\n");

#include "shell.h"
#include "progs.h" 

#include <kvnix/util.h>
#include <kvnix/mm/alloc.h>
#include <kvnix/pm/pm.h>
#include <minilib/stdlib.h>
#include <minilib/stdio.h>
#include <minilib/stdbool.h>
#include <minilib/string.h>

/* Commands includes */
#include "clear.h"
#include "../util/memdump.h"

//#include "../../test/test_list.h"
//#include "../../test/test_disk.h"
#include "../../test/test_ucontext.h"
#include "../../test/test_sem.h"
#include "../../test/test_queue.h"

#define NR_COMMANDS 6
#define CMD_NAME_DEFAULT_SIZE 8

extern void _init_timer();
extern void _stop_timer();

command_t commands_table[NR_COMMANDS] = {
	{"list", &command_list},
    {"clear", &clear_init},
	{"test_ucontext", &test_ucontext},
	{"test_sem", &test_sem},
	{"test_queue", &test_queue},
	{"shutdown", &shutdown}
}; 


PUBLIC void shell_init()
{
	command_list();
}

PRIVATE void command_list()
{
	int i;
	bool first;

	//Commands list
    puts("List of commands: ");

    first = true;
    
    for (i = 0; i < NR_COMMANDS; i++) {
        if (first) {
            first = false;
        } else {
            puts(", ");
        }
    
        puts(commands_table[i].name);
    }

    puts(", ");

    first = true;
    
    for (i = 0; i < NR_PROGS; i++) {
        if (first) {
            first = false;
        } else {
            puts(", ");
        }
    
        puts(progs_table[i].alias);
    }

    putchar('\n');

	//User interaction
    while (true)
        request_command();
}

PRIVATE void request_command()
{
    puts("$");
    
    size_t cmd_name_size = CMD_NAME_DEFAULT_SIZE * sizeof(char);
    char *command_name = kmalloc(cmd_name_size);

	getline(&command_name, &cmd_name_size, stdin);
   
    putchar('\n');

    run_command(command_name);

    kfree(command_name);
    
    putchar('\n');
}

PRIVATE void run_command(char *command_name)
{
    bool found = false;
    int i;

	//Check if it is a command
    for (i = 0; i < NR_COMMANDS && !found; i++)
        if (strcmp(command_name, commands_table[i].name) == 0)
             found = true;

	if (found) {
		commands_table[--i].init();

		return;
	}

	//Check if it is a program
    for (i = 0; i < NR_PROGS && !found; i++)
        if (strcmp(command_name, progs_table[i].alias) == 0)
             found = true;

    if (!found) {
        puts("Command not found: ");
        puts(command_name);

        return;
    }

	//Load program
	do_load_program(progs_table[--i].alias);
}

