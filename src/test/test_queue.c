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

#include <ipc/mqueue.h>
#include <minilib/stdio.h>
#include <minilib/stdlib.h>
#include <minilib/string.h>
#include <kvnix/pm/pm.h>
#include <kvnix/pm/sched.h>

extern task_t *current_task;

mqueue_t queue_values;

int prod_tasks[3];
int sum_task;
int cons_tasks[2];

mqueue_t queueValues, queueSums;

void prodBody ()
{
	int i, value = 5;

	for (i=0; i < 20; i++) {
		value++;

		printf("\nT%d produced %d", current_task->tid, value);

		//send a value
		if (mqueue_send (&queueValues, &value) < 0)
		{
		}

		//sleep for a wait
		task_sleep(value);
	}


			printf("\nT%d finished\n", current_task->tid) ;
			task_exit(0) ;
}

void sumBody ()
{
	int v0, v1, s, i;  

	for (i=0; i<10; i++) {
		//get values from queues
		mqueue_recv (&queueValues, &v0);
		mqueue_recv (&queueValues, &v1);

		//sum
		s = v0 + v1 ;
		printf ("               T%d: %d + %d = %d\n", current_task->tid, v0, v1, s);

		//send a message with the sum
		mqueue_send (&queueSums, &s);

		//sllep for a while
		task_sleep (s);
	}

    puts("Terminou a sum\n");
	task_exit(0) ;
}

void consBody()
{
	int value;

	//while(1) {
	for (int i = 0; i < 10; i++) {

		if (mqueue_recv(&queueSums, &value) < 0) {
		}
      
		printf("                                 T%d consumed %d\n", current_task->tid, value);

		//sleep for a while
		task_sleep(15);
	}


			printf("                                 T%d finished\n", current_task->tid);
			task_exit(0);
}

void test_queue() 
{
	int i;

	printf("\nStart of Message Queue Tests.") ;

	// cria as filas de mensagens (3 inteiros cada)
	mqueue_create(&queueValues, 3, sizeof(int));
	mqueue_create(&queueSums, 3, sizeof(int));
 
	printf("\nMessage Queues created.");
 
	void *stack1 = malloc(1024); 
	void *stack2 = malloc(1024); 
//	void *stack3 = malloc(1024); 
	void *stack4 = malloc(1024); 
//	void *stack5 = malloc(1024); 
///	void *stack6 = malloc(1024); 

   	//create the tasks
	sum_task = do_clone((void *)sumBody, stack1, 1024, NULL);
	cons_tasks[0] = do_clone((void *)consBody, stack2, 1024, NULL);
//	cons_tasks[1] = do_clone((void *)consBody, stack3, 1024, NULL);
   	prod_tasks[0] = do_clone((void *)prodBody, stack4, 1024, NULL);
// 	prod_tasks[1] = do_clone((void *)prodBody, stack5, 1024, NULL);
// 	prod_tasks[2] = do_clone((void *)prodBody, stack6, 1024, NULL);

   	//wait for the end of sum task
	waitpid(sum_task);

   	//destroy all queues
   	//mqueue_destroy (&queueValues);
   	//mqueue_destroy (&queueSums);
 
	printf("\nEnd of Queue Tests.") ;
}

