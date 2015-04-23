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
 * Linked list
 */

#ifndef _LIST_H_
#define _LIST_H_

/**
 * Compare function type.
 *
 * In sorted linked lists, this function is called to compare two values and
 * sort the elements. It must return a negative value representing how much less
 * is value1 than value 2 or a positive one when it is greater. If the values are
 * equal it must return zero.
 */
typedef int compare_function_t(void *value1, void *value2);

/**
 * List element.
 */
typedef struct list_elem_t {
   void *value;                     /**< value of the element */
   struct list_elem_t *prev ;       /**< previous element */
   struct list_elem_t *next ;       /**< next element */
} list_elem_t;

/**
 * Linked list.
 */
typedef struct list_t {
    list_elem_t *head;                          /**< list head */
    list_elem_t *tail;                          /**< list tail */
} list_t;

/**
 * Initializes a new list.
 *
 * @param list new list
 * @return
 */
int list_init(list_t *list);

/** 
 * Appends an element in the end of the list.
 * 
 * It throws an error when:
 * - the list does not exist
 * - the value is NULL
 *
 * @param list linked list
 * @param new element
 * @return new element
 */
list_elem_t *list_append(list_t *list, list_elem_t *elem);

/**
 * Removes a list element.
 *
 * It throws an error when:
 * - the list does not exist
 * - the list is empty
 * - the element does not exist
 * - the element is not in the list
 *
 * @param list linked list
 * @param elem linked list element
 * @return removed element
 */
list_elem_t *list_remove(list_t *list, list_elem_t *elem);

/**
 * Searches the element by value.
 *
 * @param list linked list
 * @param value element value
 * @return list element or NULL
 */
list_elem_t *list_search(list_t *list, void *value);

/**
 * Sorts the list.
 *
 * @param list linked list
 * @param compare_function function that compares two values
 * @return sorted list or NULL
 */
list_t *list_sort(list_t *list, compare_function_t *compare_function);

/**
 * Swap the position of two list elements.
 *
 * @param list linked list
 * @param elem1 list element 1
 * @param elem2 list element 2
 * @return the linked list or NULL
 */
list_t * list_swap_elements(list_t *list, list_elem_t *elem1, list_elem_t *elem2);

/**
 * Returns the list size.
 *
 * @param list linked list head
 * @return list size
 */
int list_size (list_t *list) ;

#endif

