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
 * Message Queue structure and functions.
 */

#ifndef MQUEUE_H
#define MQUEUE_H

#include <kvnix/const.h>
#include <util/list.h>

/**
 * Message structure.
 */
typedef struct mqueue_t {
	void * content;			/* content of the messages */
   
	struct list_t sending;		/* list of threads waiting to send message */
	struct list_t receiving;	/* list of threads waiting to receive message */
   
	int max;			/* max number of messages */
	int msgsize;			/* size of each message */
	int current;			/* number of messages allocated */
} mqueue_t;

/**
 * Create a message queue.
 * @param queue is a pointer to message queue structure.
 * @param msg_max is the maximum number of messages.
 * @param msg_size represents the size of each message.
 * @return 0 if the message queue was created successfully.
 */
int mqueue_create(mqueue_t *queue, int msg_max, int msg_size);

/**
 * Send a message.
 */
int mqueue_send (mqueue_t *queue, void *msg);

/**
 * Receive a message.
 */
int mqueue_recv (mqueue_t *queue, void *msg);

/**
 * Dispose a message queue structure.
 */
int mqueue_destroy (mqueue_t *queue);

/**
 * Number of messages.
 */
int mqueue_msgs (mqueue_t *queue);

#endif
