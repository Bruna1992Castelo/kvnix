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

#include <minilib/stdio.h>
#include <minilib/stdlib.h>
#include <minilib/stdbool.h>
#include <util/list.h>

__asm__(".code16gcc\n");

int list_init(list_t *list)
{
    if (list == NULL) {
		puts("The list does not exist.\n");
		return -1;
	}
 
    list->head = NULL;
    list->tail = NULL;

    return 0;
}

list_elem_t *list_append (list_t *list, list_elem_t *elem) 
{
	if (list == NULL) {
		puts("The list does not exist.\n");
		return NULL;
	}

	if (elem->prev != NULL || elem->next != NULL) {
		printf("This element is in another list.\n");
		return NULL;
	}

	if ((list->head) == NULL) {
	    //if the list is empty, the element is inserted in the list begin
		list->head = elem;
	} else {
        //otherwise, the element is inserted in the list end
        elem->prev = list->tail;
        list->tail->next = elem;
	}
    
    list->tail = elem;

    return elem;
}

list_elem_t *list_remove (list_t *list, list_elem_t *elem)
{
	//Verificando se a lista existe
	if (list == NULL) {
		puts("The list does not exist.\n");
		return NULL ;
	}
	
	//verificando se o elemento existe
	if (elem == NULL) {
		printf("This element is NULL.\n");
		return NULL;
	}

    // Verificando se a lista está vazia	
	if(list->head == NULL) {
		printf("This list is empty.\n");
		return NULL;
	}
	
	//Verificação se o elemento pertence a lista indicada
	list_elem_t *temp = list->head;
	while(temp != NULL) //buscando elemento
	{
		if(temp == elem) {
            break;
        }

   		temp = temp->next;
	}

    //se elemento nao pertence a lista retorna nulo
    if (temp != elem) {
		printf("Element not found in this list.\n");
        return NULL;
    }

    //removendo elemento
   	list_elem_t *previous = elem->prev;
   	list_elem_t *next = elem->next;

    if (previous != NULL) {
   		previous->next = next;
    } else {
   		list->head = next; //arrumando ponteiro do cabeça da lista (primeiro elemento foi removido)
    }

    if (next != NULL) {
   		next->prev = previous;
    } else {
        list->tail = previous;
	} 

	elem->next = NULL;
	elem->prev = NULL;

    return elem;
}

list_elem_t *list_search(list_t *list, void *value) 
{
    list_elem_t *temp = list->head;

	while (temp != NULL) {
		if (temp->value == value) {
            return temp;
        }

   		temp = temp->next;
	}

    return NULL;
}

list_t * list_sort(list_t *list, compare_function_t *compare_function)
{
    if (list == NULL) {
        //TODO throw an error
        return NULL;
    }

    if (list->head == NULL) {
        return list;
    }

    if (compare_function == NULL) {
        //TODO throw an error
        return NULL;
    }
    
    //The sort is done using bubble sort
    //TODO Change to a better sorting algorithm 

    bool swapped;

    do {
        swapped = false;

        list_elem_t *elem = list->head;
       
        while (elem->next != NULL) {
            if (compare_function(elem->value, elem->next->value) > 0) {
                list_swap_elements(list, elem, elem->next);
                swapped = true;
            } else {
                elem = elem->next;
            }
        }
    } while (swapped); 

    return list;
}

list_t * list_swap_elements(list_t *list, list_elem_t *elem1, list_elem_t *elem2)
{
    list_elem_t *elem1_old_prev = elem1->prev;
    list_elem_t *elem2_old_prev = elem2->prev;
    list_elem_t *elem1_old_next = elem1->next;
    list_elem_t *elem2_old_next = elem2->next;

    elem1->prev = (elem2_old_prev != elem1) ? elem2_old_prev : elem2;
    if (elem1->prev != NULL) {
        elem1->prev->next = elem1;
    } else {
        list->head = elem1;
    }

    elem1->next = (elem2_old_next != elem1) ? elem2_old_next : elem2;
    if (elem1->next != NULL) {
        elem1->next->prev = elem1;
    } else {
        list->tail = elem1;
    }
    
    elem2->prev = (elem1_old_prev != elem2) ? elem1_old_prev : elem1;
    if (elem2->prev != NULL) {
        elem2->prev->next = elem2;
    } else {
        list->head = elem2;
    }

    elem2->next = (elem1_old_next != elem2) ? elem1_old_next : elem1;
    if (elem2->next != NULL) {
        elem2->next->prev = elem2;
    } else {
        list->tail = elem2;
    }
 
    return list;
}
 
int list_size (list_t *list)
{
	list_elem_t *temp = list->head;
	int contador = 0;
	while(temp != NULL)// varre lista inteira
	{
		contador++; // incrementa o contador
		temp = temp->next;
	}
	return contador; //retorna numero de elementos
}
