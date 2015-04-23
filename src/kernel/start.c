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

#include <kvnix/start.h>

#include <kvnix/const.h>
#include <kvnix/util.h>
#include <kvnix/syscalls.h>
#include <kvnix/clock.h>
#include <kvnix/mm/mm.h>
#include <kvnix/mm/alloc.h>
#include <kvnix/pm/sched.h>
#include <kvnix/pm/pm.h>
#include <minilib/stdio.h>
#include <minilib/stdlib.h>
#include <drivers/disk.h>
#include <kvnix/ints.h>

#include "../drivers/tty/tty.h"
#include "../commands/shell/shell.h"
#include <archs/x86/regs.h>

extern void _init_interrupt();
extern proc_t system_proc;

//TODO remove it
void bg_func();

PUBLIC void _start()
{
    //console initialization
    tty_init();
 
    //system clock initialization
    system_clock_init();
 
    //scheduler initialization
    sched_init();
   
    //ints initialization
	_init_interrupt();

    //initializing the standard input/output
    stdin = kmalloc(sizeof(FILE));
    stdout = kmalloc(sizeof(FILE));
    stderr = kmalloc(sizeof(FILE));
    stdin->fd = STDIN_FILENO;
    stdout->fd = STDOUT_FILENO;
    stderr->fd = STDERR_FILENO;

    print_welcome_message();
    print_memory_info();

    //char *p = (char *) 0x505;
    //*p = 'B';

    //putchar(*p);
    //putchar('A');

    /* Background thread test */
    /*void *bg_stack = kmalloc(1024);
    
    proc_thread_t *bg_thread = sched_create_thread(current_proc, &bg_func, bg_stack, 1024, NULL);
    sched_add_thread(bg_thread); 
    */
    /* Shell thread */

    void *shell_stack = kmalloc(PROC_STACK_SIZE);
    
    task_t *shell_thread = task_create(current_proc, &shell_init, shell_stack, PROC_STACK_SIZE, NULL);
    task_add(shell_thread);
    task_join(shell_thread);

    shutdown();
//	shell_init();
}

void bg_func()
{
    while(1) {
        puts("\n[Background thread]: Good morning!\n");
        task_sleep(50);
    }
}

PRIVATE void print_welcome_message()
{
    puts("Kvnix Copyright (C) 2009 Klystofer Ortega, Victor Villela Serta\n\n");
    puts("This program comes with ABSOLUTELY NO WARRANTY.\n");
    puts("This is free software, and you are welcome to redistribute it\n"
         "under certain conditions.\n\n");

    puts("Welcome to KVNIX!\n");
    puts("<http://www.kvnix.org>\n\n");
}

PRIVATE void print_memory_info()
{
    printf("Segment: 0  Kernel Heap: [%d to %d]\n", KERNEL_HEAP_BEGIN, KERNEL_HEAP_BEGIN + KERNEL_HEAP_SIZE);

	int heap_free_space = get_free_space(system_proc.memory.heap);
	printf("Kernel Heap Space: %d\n\n", heap_free_space);
}
