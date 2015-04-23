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

#ifndef _PM_TYPES_H
#define _PM_TYPES_H

#include <kvnix/mm/types.h>
#include <minilib/ucontext.h>

/**
 * @file
 *
 * Process manager types.
 *
 * @author Victor V. Serta
 */ 

/**
 * Task status type.
 */
typedef enum task_status_t {
    TASK_CREATED,                   /**< Task was created */
    TASK_READY,                     /**< Task is ready */
    TASK_RUNNING,                   /**< Task is running */
    TASK_WAITING,                   /**< Task is waiting */
    TASK_SLEEPING,                  /**< Task is sleeping */
    TASK_ZOMBIE                     /**< Task is done */
} task_status_t;


/**
 * Process memory information.
 */
typedef struct proc_mem_t {
    memory_slot_t *region;          /**< memory region avaible to the process */
    memory_area_t *heap;            /**< memory area reserved to the heap */
} proc_mem_t;

/**
 * Process thread.
 */
typedef struct task_t {
    int tid;                        /**< thread id */ 
    char *name;                     /**< thread name */
    struct proc_t *proc;            /**< process */
    ucontext_t context;             /**< user context */
    
    task_status_t status;           /**< thread status */
    list_t join_list;               /**< threads waiting for this exits */

    long start_time;                /**< thread start time */
    long cpu_time;                  /**< cpu time */
    long last_run_time;             /**< the last time the thread run */
    long wake_up_time;              /**< time to wake up (used when it is sleeping */
    long nr_activations;            /**< number of activations */

    int exit_code;                  /**< exit code */
} task_t; 

/**
 * Process.
 */
typedef struct proc_t {
    int pid;                        /**< process id */
    int parent_pid;                 /**< parent process id */
    char *name;                     /**< process name */
    proc_mem_t memory;              /**< process memory informations */
    task_t *main_task;              /**< process main task */
} proc_t;



#endif
