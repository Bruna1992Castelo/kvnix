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
#include <kvnix/pm/pm.h>
#include <kvnix/pm/sched.h>
#include <kvnix/syscalls.h>
#include <minilib/stdio.h>
#include <minilib/stdlib.h>

extern task_t *current_task;

int s_buffer, s_item, s_slot;
int buffer[5];
int pos;

void producer() 
{
	int item = 0;
	printf("\nT%d Producer started", current_task->tid);

	while (item < 10) { 
		sem_down(s_slot) ;    //wait for a slot
		sem_down(s_buffer) ;  //wait for buffer access

		//add item to buffer
		buffer[pos++] = ++item;
		printf("\nT%d Produced: %d", current_task->tid, item) ;

		sem_up(s_buffer) ;   //release buffer access
		sem_up(s_item) ;     //raise produced items

		task_sleep(15);
		//task_sleep(0);
	}

	task_exit(0);
}

void consumer() 
{
	int i, item;

	printf("\nT%d Consumer started", current_task->tid);

	for (i=0; i < 10; i++) {
		sem_down(s_item);    //wait for the item being produced
		sem_down(s_buffer);  //wait for buffer access

		//remove item from buffer
		item = buffer[--pos]; 

		sem_up(s_buffer);	//release buffer access
		sem_up(s_slot);		//raise number of empties slots

		printf("\nT%d Consumed: %d", current_task->tid, item) ;

		task_sleep(30);
		//task_sleep(0);
	}

	task_exit(0);
}

void test_sem() 
{
	printf("\nStart of Semaphore Test") ;

	pos = 0;

	sem_init();

	//initializing semaphores
	s_buffer = sem_create(1) ;
	s_item = sem_create(0) ;
	s_slot = sem_create(5) ;

	printf("\nSemaphores created.");

	//creating task stacks
	void *stack1 = malloc(1024);
	void *stack2 = malloc(1024);

	printf("\ntasks stack created.");

	//tasks
	int task1_id = do_clone((void *)producer, stack1, 1024, NULL);
	int task2_id = do_clone((void *)consumer, stack2, 1024, NULL);

	printf("\nWaiting ending of tasks. [T%d, T%d]", task1_id, task2_id);

	waitpid(task1_id);
	waitpid(task2_id);	

    printf("\nEnd of Semaphore Test.") ;
	
    //while (1);
}

