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
 * Semaphore structure and functions.
 * 
 * @author Klystofer Ortega
 */

#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <kvnix/util.h>
#include <util/list.h>

/**
 * Semaphore structure.
 * It contains the number of resources and a list with all waiting threads.
 */
typedef struct semaphore_t {
	int count;
	int free;
	struct list_t queue;
} semaphore_t;

/**
 * Table with all created semaphores.
 */
extern semaphore_t *sem_table;

/**
 * Number of created semaphores.
 */
extern int sem_table_count;

/**
 * Initialize semaphore internal variables.
 */
void sem_init();

/**
 * Create a semaphore.
 * @param initial_value represents the amount of initial resources.
 */
int sem_create(int initial_value);

/**
 * Dispose an existing semaphore.
 * @param sem_id represents the identification of the semaphore.
 */
void sem_destroy(int sem_id);

/**
 * Add resource to the specified semaphore.
 * @param sem_id represents the identification of the semaphore.
 */
void sem_up(int sem_id);

/**
 * Request resource to the specified semaphore.
 * @param sem_id represents the identification of the semaphore.
 */
void sem_down(int sem_id);

#endif
