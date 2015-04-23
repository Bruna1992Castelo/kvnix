#include <util/list.h>
#include <minilib/stdio.h>
#include <minilib/stdlib.h>

#include "test_list.h"

__asm__(".code16gcc\n");

#define LIST_SIZE 10

int compare_function_test(void *value1, void *value2);

int values[LIST_SIZE];
list_t list1;
list_t list2;

void test_list()
{
    puts("Starting List Test\n\n");
    
    list_elem_t *aux;
    int counter;
    int *value;
    
    for (int i = 0; i < LIST_SIZE; i++) {
        values[i] = i;
    }
        
    puts("Testing list_append().\n");

    for (int i = 0; i < LIST_SIZE; i++) {
        list_elem_t *elem = malloc(sizeof(list_elem_t));
        elem->prev = NULL;
        elem->next = NULL;
        elem->value = &values[i];
        list_append(&list1, elem);
    }
    
    aux = list1.head;
    counter = 0;
    
    while (aux != NULL) {
        value = aux->value;

        if (*value != counter) {
            printf("Incorrect value %d != %d.\n", counter, *value);
            return;
        }

        aux = aux->next;
        counter++;
    }

    if (counter != LIST_SIZE) {
        printf("Expected %d elements added, but found %d.", LIST_SIZE, counter);
        return;
    }

    puts("list_append() Ok!\n\n");
    puts("Testing list_size()\n");

    int size = list_size(&list1);

    if (list_size(&list1) != LIST_SIZE) {
        printf("Expected size = %d , but found %d.", LIST_SIZE, size);
        return;
    }

    puts("list_size() Ok!\n\n");
    puts("Testing list_remove()\n");

    /* list = 0 1 2 ... (LIST_SIZE - 2) (LIST_SIZE - 1) */
    
    //remove first element
    list_elem_t *removed_elem = list_remove(&list1, list1.head);
    value = list1.head->value;

    //expected: list = 1 2 3 ... (LIST_SIZE - 2) (LIST_SIZE - 1) 
    if (*value != values[1]) {
        puts("list_remove() failed when removing first element.\n");
        return;
    }
    
    free(removed_elem);

    //remove last element
    removed_elem = list_remove(&list1, list1.tail);
    value = list1.tail->value;

    //expected: list = 1 2 3 ... (LIST_SIZE - 2) 
    if (*value != values[LIST_SIZE - 2]) {
        puts("list_remove() failed when removing last element.\n");
        return;
    }

    free(removed_elem);

    //remove element in the middle of the list
    removed_elem = list_remove(&list1, list1.head->next);
    value = list1.head->next->value;

    //expected: list = 1 3 ... (LIST_SIZE - 2) 
    if (*value != values[3]) {
        puts("list_remove() failed when removing a element in the middle of the list'.\n");
        return;
    }

    free(removed_elem);

    puts("list_remove() Ok!\n\n");
    puts("Testing list_search()\n");

    //search by a existent value
    value = list_search(&list1, &values[3])->value;
    if (*value != values[3]) {
        puts("list_search() did not found a existent value.\n");
        return;
    } 

    //search by a removed value
    if (list_search(&list1, &values[0]) != NULL) {
        puts("list_search() returned a removed value.\n");
        return;
    }

    puts("list_search() Ok!\n\n");
    puts("Testing list_swap_elements()\n");

    /* Swap elements test 1 */
    list_elem_t *elem1 = list1.head;
    list_elem_t *elem2 = elem1->next;
    list_elem_t *elem3 = elem2->next;
    list_swap_elements(&list1, elem1, elem2);

    if (list1.head != elem2) {
        puts("list_swap_elements() did not set the list head during the test 1.\n");
        return;
    }

    if (elem2->prev != NULL) {
        puts("list_swap_elements() did not set elem2->prev = NULL during the test 1.\n");
        return;
    }

    if (elem2->next != elem1) {
        puts("list_swap_elements() did not set elem2->next = elem1 during the test 1.\n");
        return;
    }
        
    if (elem1->prev != elem2) {
        puts("list_swap_elements() did not set elem1->prev = elem2 during the test 1.\n");
        return;
    }
        
    if (elem1->next != elem3) {
        puts("list_swap_elements() did not set elem1->next = elem3 during the test 1.\n");
        return;
    }
    
    if (elem3->prev != elem1) {
        puts("list_swap_elements() did not set elem3->prev = elem1 during the test 1.\n");
        return;
    }
 
    /* Swap elements test 2 */
    list_elem_t *tail_elem = list1.tail;
    list_elem_t *tail_prev_elem = tail_elem->prev;
    list_elem_t *head_elem = list1.head;
    list_elem_t *head_next_elem = head_elem->next;
    list_swap_elements(&list1, tail_elem, head_elem);

    if (list1.head != tail_elem) {
        puts("list_swap_elements() did not set the list head during the test 2.\n");
        return;
    }

    if (list1.tail != head_elem) {
        puts("list_swap_elements() did not set the list tail during the test 2.\n");
        return;
    }

    if (list1.head->next != head_next_elem) {
        puts("list_swap_elements() did not set tail_elem->next = head_next_elem during the test 2.\n");
        return;
    }
    
    if (list1.head->prev != NULL) {
        puts("list_swap_elements() did not set tail_elem->prev = NULL during the test 2.\n");
        return;
    }
     
    if (list1.tail->prev != tail_prev_elem) {
        puts("list_swap_elements() did not set head_elem->prev = tail_prev_elem during the test 2.\n");
        return;
    }
 
    if (list1.tail->next != NULL) {
        puts("list_swap_elements() did not set head_elem->next = NULL during the test 2.\n");
        return;
    }
        
    puts("list_swap_elements() Ok!\n\n");
    puts("Testing list_sort()\n");

    for (int i = LIST_SIZE - 1; i >= 0; i--) {
        list_elem_t *elem = malloc(sizeof(list_elem_t));
        elem->prev = NULL;
        elem->next = NULL;
        elem->value = &values[i];
        list_append(&list2, elem);
    }
    
    list_sort(&list2, &compare_function_test);
    
    aux = list2.head;
    counter = 0;
    
    while (aux != NULL) {
        value = aux->value;

        if (*value != counter) {
            printf("Incorrect value %d != %d.\n", counter, *value);
            return;
        }

        aux = aux->next;
        counter++;
    }
    
    puts("list_sort() Ok!\n\n");
    puts("End of Tests.\n");

}

int compare_function_test(void *value1, void *value2)
{
    int i1 = *((int *) value1);
    int i2 = *((int *) value2);

    return i1 - i2;
}
