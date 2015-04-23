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

#ifndef _SCHED_H
#define _SCHED_H

#include <sys/types.h>
#include <kvnix/const.h>
#include <kvnix/pm/types.h>
#include <kvnix/pm/const.h>
#include <minilib/ucontext.h>
#include <minilib/stdbool.h>

/**
 * @file
 *
 * Scheduler functions.
 *
 * @author Victor V. Serta
 */ 

/**
 * System process.
 */
extern proc_t system_proc;

/**
 * Current process.
 */
extern proc_t *current_proc;

/**
 * Dispatcher task list element.
 */
extern task_t *dispatcher_task;

/**
 * Current task list element.
 */
extern task_t *current_task;

/**
 * Scheduler initialization.
 */
PUBLIC void sched_init();
  
/**
 * Creates a new task.
 *
 * @param proc owner process
 * @param func start function
 * @param child_stack task stack
 * @param arg start function parameter
 * @return new task
 */
PUBLIC task_t * task_create(proc_t *proc, int (*func)(void *), void *child_stack, size_t child_stack_size, void *arg);

/**
 * Add a new task to the ready list.
 *
 * @param new_task new ready task
 */
PUBLIC void task_add(task_t *new_task);

/**
 * Defines the dispatcher as the current task.
 */
PUBLIC void task_yield();

/**
 * Defines the current task.
 *
 * @param task task
 */
PUBLIC void task_switch(task_t *task);

/**
 * Defines the current task as blocked util the other
 * task exits.
 * 
 * @param task task
 * @return task exit value
 */
PUBLIC int task_join(task_t *task);

/**
 * Defines the current task as sleeping.
 * 
 * @param ticks clock ticks
 */
PUBLIC void task_sleep(long ticks);

/**
 * Exits the task.
 * 
 * @param exit_code exit code
 */
PUBLIC void task_exit(int exit_code);

/**
 * Handles the timer interruption.
 */
PUBLIC void sched_handle_timer();

/**
 * Returns a task by its id.
 *
 * @param pid task id
 * @return task
 */
PUBLIC task_t * get_task_by_pid(int pid);

/**
 * Schedules the next task. 
 *
 * @return next task list element
 */
PUBLIC list_elem_t * schedule();

/**
 * Dispatcher.
 */
PUBLIC void dispatcher_body();

#endif
