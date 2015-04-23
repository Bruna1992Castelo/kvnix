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

#include <kvnix/util.h>
#include <kvnix/pm/pm.h>
#include <kvnix/pm/sched.h>
#include <kvnix/mm/alloc.h>
#include <kvnix/clock.h>
#include <drivers/disk.h>
#include <minilib/stdlib.h>
#include <minilib/string.h>
#include <archs/x86/regs.h>
#include <minilib/stdio.h>

#include "../commands/shell/progs.h"

#define NR_USER_SEGMENTS 5

#define SEGMENT_FREE 0
#define SEGMENT_ALLOCATED 1

extern proc_t system_proc;
int user_segments[NR_USER_SEGMENTS];

void load_from_disk(const char *name, unsigned short ds);
image_sect_t * get_program_by_alias(const char * alias);

void do_load_program(const char *name) 
{
    /*
    proc_t *current_process = current_task->proc;
    
    //process id
    int new_parent_pid = current_process->pid;
    int new_pid = get_next_pid();
    
    //new process creation
    proc_t *new_process = processes[new_pid];
    new_process->parent_pid = new_parent_pid;
    new_process->pid = new_pid;
    new_process->pid = name; 
    */

    enable_preemption(false);

    puts("Loading...\n");

    //TODO remove          
    proc_t *new_process = kmalloc(sizeof(proc_t));
	if (new_process == NULL)
		panic(PM_NAME, "Unable to allocate memory at do_load_program().");
    

    //main task setup
    task_t *new_main_task = task_create(new_process, (void *) PROC_CODE_BEGIN, 
            (void *) PROC_STACK_BEGIN, PROC_STACK_SIZE, NULL);

    new_process->pid = new_main_task->tid;
    new_process->main_task = new_main_task;
    
    proc_mem_t *new_memory = &new_process->memory;
    
    //free segment search
    int segment_index;
    for (segment_index = 0; segment_index < NR_USER_SEGMENTS; segment_index++) {
        if (user_segments[segment_index] == SEGMENT_FREE) {
            break;
        }
    }

    if (segment_index == NR_USER_SEGMENTS) {
        panic(PM_NAME, "Unable to load program: Out of memory.");
    }
    
    user_segments[segment_index] = SEGMENT_ALLOCATED;

    unsigned int segment_begin = (unsigned int) (0x10000 + segment_index * 0x10000); 
    reg_t segment_number = (size_t) segment_begin >> 4; 
    
    //defining the segment
    mcontext_t *new_machine_context = &new_main_task->context.uc_mcontext;
    new_machine_context->mc_cs = (reg_t) segment_number;
    new_machine_context->mc_ds = (reg_t) segment_number;
    new_machine_context->mc_es = (reg_t) segment_number;
    new_machine_context->mc_ss = (reg_t) segment_number;

	reg_t kernel_ds = 0;

    //heap setup 
	memory_area_t *heap;

	CHANGE_DATA_SEGMENT(segment_number);
    heap = init_memory_area(PROC_HEAP_BEGIN, PROC_HEAP_SIZE); 
	CHANGE_DATA_SEGMENT(kernel_ds);

	new_memory->heap = heap;

    //load the program
    load_from_disk(name, segment_number);

    //show process informations
    printf("\nProgram loaded (PID %d)\n  Segment: %d Code: [%d-%d] Heap:[%d-%d] Stack:[%d-%d]\n", 
            new_process->pid,
            segment_number, PROC_CODE_BEGIN, (PROC_CODE_BEGIN + PROC_CODE_SIZE),
            PROC_HEAP_BEGIN, (PROC_HEAP_BEGIN + PROC_HEAP_SIZE),
            PROC_STACK_BEGIN, (PROC_STACK_BEGIN + PROC_STACK_SIZE));

    //waiting the main thread
    task_add(new_main_task);
	task_join(new_main_task);
    
    //when the processes is finished...
    user_segments[segment_index] = SEGMENT_FREE;
    kfree(new_process);

	//show free heap space
	//int heap_free_space = get_free_space(system_proc.memory.heap);
	//printf("\nFree Heap Space.\nTotal: %d\n", heap_free_space);
}

void load_from_disk(const char *name, unsigned short ds)
{
	image_sect_t * prog = get_program_by_alias(name);

	if (prog == NULL) {
		panic(PM_NAME, "Program not found at load_from_disk().");
		return;
	}

	int i;
    char *mem = kmalloc(512);
	if (mem == NULL)
		panic(PM_NAME, "Unable to allocate memory at load_from_disk().");

	unsigned int offset = 0;
	unsigned short dst = 0x10;
	unsigned short src = (unsigned short)mem;
	unsigned short current_ds = 0;

	//load sect by sect from disk
	for (i = 0; i < prog->nrsects; i++) {
    	read_disk_data(mem, prog->start + offset, 1);

		BYTE_COPY2(ds, (void *)dst, current_ds, (void *)mem, 512);		

		dst += 512;
		offset += 512;
	}

    kfree(mem);
}

image_sect_t * get_program_by_alias(const char * alias) {
	int i;

	for (i = 0; i < NR_PROGS; i++) {
		if (strcmp(alias, progs_table[i].alias) == 0)
			return &progs_table[i];
	}

	return NULL;
}
