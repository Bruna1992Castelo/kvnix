
#include "test_mm.h"
#include <kvnix/mm/mm.h>

#include <minilib/stdlib.h>
#include <minilib/stdio.h>

__asm__(".code16gcc\n");

#define MEMORY_AREA_TEST_BEGIN 0x7FFFF
#define MEMORY_AREA_TEST_SIZE 0x500
#define SLOT1_SIZE 0x100
#define SLOT2_SIZE 0x350


void print_slots_info(memory_area_t *memory_area)
{
    puts("Free:");
    print_slots(memory_area->free_slots);

    puts("Allocated:");
    print_slots(memory_area->allocated_slots);
}

void test_mm()
{
    list_t *free_slots;
    free_slots = malloc(sizeof(list_t));
    free_slots->head = NULL;
    free_slots->tail = NULL;
    
    list_t *allocated_slots;
    allocated_slots = malloc (sizeof(list_t));
    allocated_slots->head = NULL;
    allocated_slots->tail = NULL;
                                  
    memory_area_t *memory_area;
    memory_area = malloc(sizeof(memory_area_t));
    memory_area->free_slots = free_slots;
    memory_area->allocated_slots = allocated_slots;

    memory_slot_t *first_slot = add_free_slot(memory_area, (void *) MEMORY_AREA_TEST_BEGIN, MEMORY_AREA_TEST_SIZE);
    
    printf("Slot header size: %d bytes.\n\n", SLOT_HEADER_SIZE);
    print_slots_info(memory_area);

    /* ---- */

    printf("\nTrying to allocate %d bytes... \n", SLOT1_SIZE);
    memory_slot_t *slot1 = allocate_memory_slot(memory_area, SLOT1_SIZE);
    
    if (slot1 == NULL) {
        puts("Slot1 was not allocated.\n");
        return;
    }

    if (slot1->size != SLOT1_SIZE) {
        printf("Expected slot1->size == %d, but found %d.\n", SLOT1_SIZE, (int) slot1->size);
        return;
    }

    if (!(slot1->status & ALLOCATED_SLOT_MASK)) {
        printf("Expected slot1->status == %d (allocated), but found %d.\n", ALLOCATED_SLOT_MASK, (int) slot1->status);
        return;
    }

    print_slots_info(memory_area);

    /* ---- */

    printf("\nTrying to allocated %d bytes (this is more than available)... \n", MEMORY_AREA_TEST_SIZE);
    memory_slot_t *slot2 = allocate_memory_slot(memory_area, MEMORY_AREA_TEST_SIZE);

    if (slot2 != NULL) {
        printf("Expected a NULL slot, but found %d bytes.\n", (int) slot2->size);
        return;
    }
    
    puts("Ok! It returned a NULL memory slot.\n");

    
    /* ---- */

    printf("\nTrying to allocate %d bytes... \n", SLOT2_SIZE);
    slot2 = allocate_memory_slot(memory_area, SLOT2_SIZE);
    
    if (slot2 == NULL) {
        puts("Slot2 was not allocated.\n");
        return;
    }

    if (slot2->size != SLOT2_SIZE) {
        printf("Expected slot2->size == %d, but found %d.\n", SLOT2_SIZE, (int) slot2->size);
        return;
    }

    if (!(slot2->status & ALLOCATED_SLOT_MASK)) {
        printf("Expected slot2->status == %d (allocated), but found %d.\n", ALLOCATED_SLOT_MASK, (int) slot2->status);
        return;
    }

    print_slots_info(memory_area);
    
    /* ---- */

    puts("\nFreeing slot2... ");
    slot2 = free_memory_slot(memory_area, slot2);

    if (slot2 == NULL) {
        puts("\nSlot 2 was not found...\n");
        return;
    }
    
    puts("\nFreeing slot1... \n");
    slot1 = free_memory_slot(memory_area, slot1);
    
    if (slot1 == NULL) {
        puts("Slot 1 was not found...\n");
        return;
    }
        
    print_slots_info(memory_area);
 
    /* ---- */

    printf("\nTrying to allocate %d bytes (slot1 + slot 2 size)... \n", SLOT1_SIZE + SLOT2_SIZE);
    slot1 = allocate_memory_slot(memory_area, SLOT1_SIZE + SLOT2_SIZE);
    
    if (slot1 == NULL) {
        puts("Slot1+Slot2 was not allocated.\n");
        return;
    }

    if (slot1->size != (SLOT1_SIZE + SLOT2_SIZE)) {
        printf("Expected slot->size == %d, but found %d.\n", SLOT1_SIZE + SLOT2_SIZE, (int) slot1->size);
        return;
    }

    if (!(slot1->status & ALLOCATED_SLOT_MASK)) {
        printf("Expected slot->status == %d (allocated), but found %d.\n", ALLOCATED_SLOT_MASK, (int) slot1->status);
        return;
    }

    print_slots_info(memory_area);
}

