/* Copyright (C) 2009 Klystofer Ortega, Victor Villela Serta
   This file is part of Kvnix.

   Kvnix is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General  License as 
   published by the Free Software Foundation, either version 3 of 
   the License, or (at your option) any later version.

   Kvnix is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Lesser General  License for more details.

   You should have received a copy of the GNU Lesser General  
   License along with Kvnix. If not, see <http://www.gnu.org/licenses/>. 
*/

#include <kvnix/mm/mm.h>
#include <kvnix/util.h>
#include <minilib/stdlib.h>
#include <minilib/stdio.h>
#include <minilib/string.h>
#include <util/list.h>

#define MM_NAME "Memory manager"

__asm__(".code16gcc\n");

/**
 * Defines the slot as allocated.
 *
 * @param slot_elem list element with the slot
 */
void define_slot_as_allocated(memory_area_t *memory_area, list_elem_t *slot_elem);

/**
 * Defines the slot as free.
 *
 * @param slot_elem list element with the slot
 */
void define_slot_as_free(memory_area_t *memory_area, list_elem_t *slot_elem);

/**
 * Merges a memory slot with its neighbor, if possible.
 *
 * @param slot_elem list element with the slot
 */
void merge_free_memory_slot_with_neighbors(memory_area_t *memory_area, list_elem_t *slot_elem);

/**
 * Merges two memory slots, if possible.
 *
 * @param slot_elem1 list element with the slot 1
 * @param slot_elem2 list element with the slot 2
 */
void * merge_memory_slots(memory_area_t *memory_area, list_elem_t *slot1_elem, list_elem_t *slot2_elem);

/**
 * Splits a memory slot, if necessary.
 *
 * @param memory_area memory area
 * @param slot memory slot
 * @param size size
 * @return memory slot or NULL
 */
memory_slot_t * split_memory_slot(memory_area_t *memory_area, memory_slot_t *slot, size_t size);

/**
 * Compares two memory slots by their positions in the memory.
 * This function is called during the sort of free/allocated slot list.
 *
 * @param slot1 slot 1
 * @param slot2 slot 2
 * @return comparation result (-1: less, 0: equal, 1: greater)
 */
int compare_slots_positions(void *slot1, void *slot2);


memory_area_t * init_memory_area(void *begin, size_t size)
{
    size_t real_size = size - (2 * sizeof(list_t) + sizeof(memory_area_t));
    
    size_t begin_position = (size_t) begin;

	memory_area_t *memory_area = (void *) begin_position;
    
	list_t *free_slots = (void *) (begin_position + sizeof(memory_area_t));
    free_slots->head = NULL;
    free_slots->tail = NULL;
    
    list_t *allocated_slots = (void *) (begin_position + sizeof(list_t) + sizeof(memory_area_t));
    allocated_slots->head = NULL;
    allocated_slots->tail = NULL;
    
    void *slot_begin = (void *) (begin_position + (2 * sizeof(list_t)) + sizeof(memory_area_t));

    memory_area->free_slots = free_slots;
    memory_area->allocated_slots = allocated_slots;

   	add_free_slot(memory_area, slot_begin, real_size);
	return memory_area;
}


memory_slot_t * add_free_slot(memory_area_t *memory_area, void *begin, size_t size)
{
    //defining the pointers positions
    size_t list_elem_position = (size_t) begin;
    size_t slot_position = list_elem_position + sizeof(list_elem_t);
    
	size_t usable_memory_begin_position = slot_position + sizeof(memory_slot_t);

    //the begin position of the slot constains an element of a linked list
    list_elem_t *elem = (void *) list_elem_position;

    //after the list element is the slot descriptor
    memory_slot_t *slot = (void *) slot_position;
    
    //after the slot is the usable memory begin
    slot->begin = (void *) usable_memory_begin_position;

    //by default, the usable memory contains a debug message
    char *debug_message = (void *) usable_memory_begin_position;

    //defining the list element
    elem->prev = NULL;
    elem->next = NULL;

    //the value is the slot descriptor
    elem->value = slot;

    //slots less than the header size are ignored
    if (size < SLOT_MIN_SIZE) {
        panic(MM_NAME, "The size is not enough to store the memory slot header.");
    }

    //defining the slot attributes
    slot->magic_number = MEMORY_SLOT_MAGIC_NUMBER;
    slot->size = size - SLOT_HEADER_SIZE;
    slot->status = 0x00;
    
    //defining the debug message
    slot->debug_message = debug_message;
    slot->debug_message[0] = 'F';
    slot->debug_message[1] = 'R';
    slot->debug_message[2] = 'E';
    slot->debug_message[3] = 'E';
    slot->debug_message[4] = '\0';
    
    //the new slot is appended to the free slot list
    if (list_append(memory_area->free_slots, elem) == NULL) {
        panic(MM_NAME, "Adding a new free slot failed in add_free_slot().");
    }

    //sorting the free slot list by memory position
    list_sort(memory_area->free_slots, compare_slots_positions);

    //the new slot is merged with its neighbors, if possible
    merge_free_memory_slot_with_neighbors(memory_area, elem);

    return slot;
}

 memory_slot_t * allocate_memory_slot(memory_area_t *memory_area, size_t size)
{
	size = (size < 100)?100:size;

    list_elem_t *elem = memory_area->free_slots->head;

    //iterate to find a slot with the size necessary (first-fit)
    while (elem != NULL) {
        memory_slot_t *slot = elem->value;

        //checking the magic number
        if (slot->magic_number != MEMORY_SLOT_MAGIC_NUMBER) {
            panic(MM_NAME, "Invalid magic number found in allocate_memory_slot().");
        }


        if (slot->size >= size) {
            //defining allocated
            define_slot_as_allocated(memory_area, elem);
            
            //a slot with the necessary size was found. trying to split it...
            split_memory_slot(memory_area, slot, size);

            //returning the slot
            return slot;
        }

        elem = elem->next; 
    }                 
    
    //TODO throw "out of memory" error
    return NULL;
}

 memory_slot_t * free_memory_slot(memory_area_t *memory_area, void *begin) 
{
    //defining the slot position                                        
    size_t slot_position = (size_t) begin - sizeof(memory_slot_t);
    
    //getting the slot in that position
    memory_slot_t *slot = (void *) slot_position; 
 
    //the linked list element is before the slot description
    list_elem_t *elem = get_memory_slot_header_begin(slot); 
 
    //is it really a list element that contains a memory slot?
    memory_slot_t *elem_value = elem->value; 
    if (elem_value->magic_number != MEMORY_SLOT_MAGIC_NUMBER) {
        return NULL;
    }
 
    define_slot_as_free(memory_area, elem);
    
    return slot;
}

 memory_slot_t * reallocate_memory_slot(memory_area_t *memory_area, void *begin, size_t new_size)
{
    //defining the slot position                                        
    size_t old_slot_position = (size_t) begin - sizeof(memory_slot_t);
    
    //getting the slot in that position
    memory_slot_t *old_slot = (void *) old_slot_position;
    
    //is it really a list element that contains a memory slot?
    if (old_slot->magic_number != MEMORY_SLOT_MAGIC_NUMBER) {
        return NULL;
    }

    //it is not necessary to reallocate
    if (new_size <= old_slot->size) {
        return old_slot;
    }
    
    memory_slot_t *new_slot = allocate_memory_slot(memory_area, new_size);

    memcpy(new_slot->begin, old_slot->begin, old_slot->size);

    //the linked list element is before the slot description
    list_elem_t *elem = get_memory_slot_header_begin(old_slot); 

    define_slot_as_free(memory_area, elem);

    return new_slot;
}
 
 void print_slots(list_t *slot_list)
{
    list_elem_t *elem = slot_list->head;

    int i = 0;

    while (elem != NULL) {
        if (i++ > 10) {
            break;
        }

        memory_slot_t *slot = elem->value;

        size_t begin = (size_t) slot->begin;
        size_t size = slot->size;
        size_t end = (size_t) get_memory_slot_end(slot);

        printf("[%d | %d (%d) %d]", (int) slot, (int) begin, (int) size, (int) end);

        elem = elem->next;
    }

    puts("\n");
}

 void print_memory_area(memory_area_t *memory_area)
{
    puts("\nFree mem:");
    print_slots(memory_area->free_slots);

    puts("\nAllocated mem:");
    print_slots(memory_area->allocated_slots);
    
    puts("\n");
}

 void define_slot_as_allocated(memory_area_t *memory_area, list_elem_t *slot_elem)
{
    memory_slot_t *slot = slot_elem->value;

    //the slot is defined as allocated
    slot->status |= ALLOCATED_SLOT_MASK;
    slot->debug_message[0] = 'A';

    //the slot must be removed from the free list and added to the allocated list
    if (list_remove(memory_area->free_slots, slot_elem) == NULL) {
        panic(MM_NAME, "Removing an free slot failed in define_slot_as_allocated().");
    }
    
    if (list_append(memory_area->allocated_slots, slot_elem) == NULL) {
        panic(MM_NAME, "Adding an allocated slot failed in define_slot_as_allocated().");
    }
    
    //sorting the allocated slot list by memory position
    list_sort(memory_area->allocated_slots, &compare_slots_positions);
}
 
 void define_slot_as_free(memory_area_t *memory_area, list_elem_t *slot_elem)
{
    memory_slot_t *slot = slot_elem->value;

    //the slot is defined as free
    slot->status &= !ALLOCATED_SLOT_MASK;
    slot->debug_message[0] = 'F';
    slot->debug_message[1] = 'R';
    slot->debug_message[2] = 'E';
    slot->debug_message[3] = 'E';
    slot->debug_message[4] = '\0';

    //the slot must be removed from the allocated list and added to the free list
    if (list_remove(memory_area->allocated_slots, slot_elem) == NULL) {
        panic(MM_NAME, "Removing an allocated slot failed in define_slot_as_free().");
    }
    if (list_append(memory_area->free_slots, slot_elem) == NULL) {
        panic(MM_NAME, "Adding an free slot failed in define_slot_as_free().");
    }

    //sorting the free slot list by memory position
    list_sort(memory_area->free_slots, &compare_slots_positions);

    //the slot is merged with its neighbors, if possible
    merge_free_memory_slot_with_neighbors(memory_area, slot_elem);
}

 void merge_free_memory_slot_with_neighbors(memory_area_t *memory_area, list_elem_t *slot_elem)
{
    list_elem_t *prev = slot_elem->prev;
    list_elem_t *next = slot_elem->next;
    
    if (prev != NULL) {
        slot_elem = merge_memory_slots(memory_area, prev, slot_elem);
    }
    
    if (next != NULL) {
        slot_elem = merge_memory_slots(memory_area, slot_elem, next);
    }
}

 void * merge_memory_slots(memory_area_t *memory_area, list_elem_t *slot1_elem, list_elem_t *slot2_elem)
{
    memory_slot_t *slot1 = slot1_elem->value;
    memory_slot_t *slot2 = slot2_elem->value;
    
    size_t slot1_begin_position = (size_t) get_memory_slot_header_begin(slot1);
    size_t slot1_end_position = (size_t) get_memory_slot_end(slot1);
    
    size_t slot2_begin_position = (size_t) get_memory_slot_header_begin(slot2);

    //is it continous?
    if ((slot1_end_position + 1) != slot2_begin_position) {
        //if not just slot2_elem is returned
        return slot2_elem;
    }

    //adds the sizes 
    slot1->size += (slot2->size + SLOT_HEADER_SIZE);

    //the slot2 must be removed from the free list
    list_remove(memory_area->free_slots, slot2_elem);

    return slot1_elem;
}

 memory_slot_t * split_memory_slot(memory_area_t *memory_area, memory_slot_t *slot, size_t size)
{
    size_t new_slot_size = slot->size - size;
    
    if (new_slot_size >= SLOT_MIN_SIZE) {
        slot->size = size;

        size_t new_slot_begin_position = (size_t) get_memory_slot_end(slot) + 1; 
        void *new_slot_begin = (void *) new_slot_begin_position;
    
        add_free_slot(memory_area, new_slot_begin, new_slot_size);
    }

    return slot;
}
    
 int compare_slots_positions(void *slot1, void *slot2)
{
    return slot1 - slot2;
}

 int get_free_space(memory_area_t *memory_area) 
{
	int size = 0;
	memory_slot_t *slot;

	list_elem_t *elem = memory_area->free_slots->head;

	while (elem != NULL) {
		slot = elem->value;

		size += slot->size;

		elem = elem->next;
	}

	return size;
}
