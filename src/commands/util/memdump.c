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

#include "memdump.h"

#include <minilib/stdio.h>
#include <minilib/stdlib.h>
#include <minilib/stdbool.h>
#include <kvnix/const.h>

__asm__(".code16gcc\n");

#define POSITIONS_PER_PAGE 5

void memdump()
{
    //forces the pointer to the heap begin position
    char *mem = (char *) KERNEL_HEAP_BEGIN;

    bool new_page;
    int position;

    const char *info_template = "\nMemory dump (from: %d to: %d)\n%s\n";

    //from 0x0 to 0x3FF: Interrupt Vector Tamble
    printf(info_template, 0x0, 0x3FF, "Interrupt Vector Table");

    //from 0x400 to 0x4FF: BIOS data area
    printf(info_template, 0x400, 0x4FF, "BIOS data area");

    //from 0x500 to 0x7BFF: Heap
    for (int i = 0; i < KERNEL_HEAP_SIZE; i++) {
        position = KERNEL_HEAP_BEGIN + i;
        new_page = ((i % POSITIONS_PER_PAGE) == 0);

        if (new_page) {
            //if it is a new page then it prints information about the memory range
            printf(info_template, position, position + POSITIONS_PER_PAGE, "Heap");
        }

        printf("%d: %c \n", position, *(mem + i));

        if ((i > 0) && new_page) {
            printf("\nPress any key to continue or 'q' to quit.\n\n");
            char option = getchar();

            if (option == 'q') {
                return;
            }
        }
    }
}


