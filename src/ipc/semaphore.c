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

#include <ipc/semaphore.h>
#include <kvnix/pm/sched.h>
#include <kvnix/pm/const.h>
#include <kvnix/pm/types.h>
#include <kvnix/clock.h>
#include <kvnix/mm/alloc.h>
#include <kvnix/util.h>

semaphore_t *sem_table;
int sem_table_count;

task_t *current_task;
list_t ready_tasks;

/**
 * Create a semaphore to kernel space.
 */ 
int add_semaphore();

void sem_init() 
{
	sem_table_count = 0;
	sem_table = NULL;
}

int sem_create(int initial_value) 
{
	int sem_idx = add_semaphore();
	semaphore_t *sem = &sem_table[sem_idx];

	//initital resources
	sem->count = initial_value;

	//initialize semaphore list
	list_init(&sem->queue);

	//add semaphore struct to the kernel semaphore table
	return sem_idx;
}

void sem_destroy(int sem_id) 
{
	if (sem_id < 0 || sem_id >= sem_table_count)
		panic("Semaphore", "Destroying semaphore.");

	//TODO release all tasks

	//free table position
	sem_table[sem_id].free = 1;
}

void sem_up(int sem_id) 
{	
	enable_preemption(false);
 
	if (sem_id < 0 || sem_id >= sem_table_count)
		panic("Semaphore", "Destroying semaphore.");

	semaphore_t *s = &sem_table[sem_id];  
	s->count++;

	//remove task from suspended queue (FIFO)
	if (s->count <= 0) {

		list_elem_t *elem = list_remove(&s->queue, s->queue.head);
		elem->next = NULL;
		elem->prev = NULL;

		task_t *waiting_task = elem->value;
		waiting_task->status = TASK_READY;

		if (list_append(&ready_tasks, elem) == NULL)
			panic("Semaphore", "Adding a task to the ready list in sem_up().");
	}
	   
	enable_preemption(true);
}

void sem_down(int sem_id) 
{
	enable_preemption(false);

	if (sem_id < 0 || sem_id >= sem_table_count)
		panic("Semaphore", "Destroying semaphore.");

	semaphore_t *s = &sem_table[sem_id];
	s->count--;

	//add current task to the semaphore queue (blocking)
	if (s->count < 0) {
		list_elem_t *elem = kmalloc(sizeof(list_elem_t));
		elem->next = NULL;
		elem->prev = NULL;
		elem->value = current_task;

		current_task->status = TASK_WAITING;
		if (list_append(&s->queue, elem) == NULL)
			panic("Semaphore", "Adding a task to the semaphore queue in sem_down().");	

		//return to dispatcher
		task_yield();
	}
   
	enable_preemption(true);
}

int add_semaphore() 
{
	int i, sem_idx;

	if (sem_table_count == 0) {
		sem_table = (semaphore_t *)kmalloc(sizeof(semaphore_t));

		sem_idx = 0;
		sem_table_count++;
	}
	else {
		sem_idx = -1;

		//look for a unused space
		for (i=0; i < sem_table_count && sem_idx < 0; i++)
			if (sem_table[i].free == 1)
				sem_idx = i;
	
		//case all slot are being used, have to create one
		if (sem_idx < 0) {
			sem_idx = sem_table_count++;

			sem_table = (semaphore_t *)krealloc(sem_table, sizeof(semaphore_t)*sem_table_count);
		}
	}

	sem_table[sem_idx].free = 0;

	return sem_idx;
}

