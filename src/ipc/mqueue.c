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
#include <ipc/mqueue.h>
#include <kvnix/clock.h>
#include <kvnix/mm/alloc.h>
#include <kvnix/pm/pm.h>
#include <kvnix/pm/sched.h>
#include <minilib/stdio.h>
#include <minilib/stdlib.h>
#include <minilib/string.h>

#define MQ_NAME "Message Queue"

task_t *current_task;
list_t ready_tasks;

int mqueue_create(mqueue_t *queue, int msg_max, int msg_size) 
{
	int result = -1;

	enable_preemption(true);
   
	//message size must be between 1 and 256
	if ( !(msg_size >= 1 && msg_size <= 256) ) {
		return -2;
	}
   
	//max message number must be between 1 and 100
	if ( !(msg_max >= 1 && msg_max <= 100) ) {
		return -3;
	}
   
	//allocation mqueue struct and initializing values
	queue->content = kmalloc(msg_max*msg_size);

	if (queue->content != NULL) {
		queue->max = msg_max;
		queue->msgsize = msg_size;
		queue->current = 0;

		list_init(&queue->sending);
		list_init(&queue->receiving);

		result = 0;
	}
  
	enable_preemption(false); 

	return (result);
}

int mqueue_send(mqueue_t *queue, void *msg) 
{
	int result = -1;
   
	//check if there is an empty slot for a new message
	//otherwise, should put current task to wait
	while (queue->current == queue->max) {
		list_elem_t *elem = kmalloc(sizeof(list_elem_t));

		if (elem == NULL)
			panic(MQ_NAME, "Unable to allocate element at mqueue_send().");

		elem->next = NULL;
		elem->prev = NULL;
		elem->value = current_task;

		current_task->status = TASK_WAITING;

		list_append(&queue->sending, elem);      

		task_yield();
	}
   
	enable_preemption(true); 
   
	//an empty slot is free
	if (queue->content != NULL) {

		//copy the message into mqueue content 
		void * c = queue->content;
		c += (queue->current*queue->msgsize);
  
		memcpy(c, msg, queue->msgsize);

		//add number of messages
		queue->current++;

		//check if there is at least a task waiting to receive message
		if (list_size(&queue->receiving) > 0) {

			list_elem_t *e = list_remove(&queue->receiving, queue->receiving.head);
			e->next = NULL;
			e->prev = NULL;

			task_t *waiting_task = e->value;
			waiting_task->status = TASK_READY;
			
			//add it to dispatcher ready list
			if (list_append(&ready_tasks, e) == NULL)
				panic(MQ_NAME, "Adding a task to the ready list in mqueue_send().");
		}

		result = 0;
	}
   
	enable_preemption(false); 
   
	return result;
}

int mqueue_recv (mqueue_t *queue, void *msg) 
{
	int result = -1;
   
	//blocking task
	//wait until receive a message
	while (queue->current == 0) {
		list_elem_t *elem = kmalloc(sizeof(list_elem_t));

		if (elem == NULL)
			panic(MQ_NAME, "Unable to allocate element at mqueue_recv().");

		elem->next = NULL;
		elem->prev = NULL;
		elem->value = current_task;

		current_task->status = TASK_WAITING;

		if (list_append(&queue->receiving, elem) == NULL)
			panic(MQ_NAME, "Adding a task to the receiving list at mqueue_recv().");

		task_yield();
	}
 
	enable_preemption(true); 
   
	if (queue->content != NULL) {
		void * c = queue->content;
      
		//copy first message to msg
		//remove first message from mqueue
		memcpy(msg, c, queue->msgsize);

		queue->current--;

		memcpy(c, c+queue->msgsize, queue->msgsize*queue->current);
            
		//check if exists a task waiting to send message
		if (list_size(&queue->sending) > 0) {
			list_elem_t *e = list_remove(&queue->sending, queue->sending.head);
			e->next = NULL;
			e->prev = NULL;

			task_t *waiting_task = e->value;
			waiting_task->status = TASK_READY;
			
			if (list_append(&ready_tasks, e) == NULL)
				panic(MQ_NAME, "Adding a task to the ready list at mqueue_recv().");
		}
      
		result = 0;
	}

	enable_preemption(false); 
   
	return result;
}

int mqueue_destroy(mqueue_t *queue) 
{
	enable_preemption(true); 
   
	//dispose all messages
	kfree(queue->content);
	queue->content = NULL;

	queue->current = -1;
	queue->max = 0;
	queue->msgsize = 0;

	list_elem_t *e = NULL;

	//release tasks waiting to send
	while ((e = queue->sending.head) != NULL) {

		e = list_remove(&queue->sending, queue->sending.head);
		e->next = NULL;
		e->prev = NULL;
		task_t *waiting_task = e->value;
		waiting_task->status = TASK_READY;

		if (list_append(&ready_tasks, e->value) == NULL)
			panic(MQ_NAME, "Adding a task to the ready (send) list at mqueue_destroy().");
	}

	//release tasks waiting for messages
	while ((e = queue->receiving.head) != NULL) {
      
		e = list_remove(&queue->receiving, queue->receiving.head);
		e->next = NULL;
		e->prev = NULL;
		task_t *waiting_task = e->value;
		waiting_task->status = TASK_READY;

		if (list_append(&ready_tasks, e->value) == NULL)
			panic(MQ_NAME, "Adding a task to the ready (recv) list at mqueue_destroy().");
	}
   
	enable_preemption(false); 
   
	return 0;
}

int mqueue_msgs (mqueue_t *queue) 
{
   return (queue->current);
}

