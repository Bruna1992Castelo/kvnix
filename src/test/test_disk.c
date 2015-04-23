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

#include "test_disk.h"
#include <stdio.h>
#include <minilib/malloc.h>
#include <drivers/disk.h>

void test_disk() {

    printf("\nStarting disk test.");

	char * memory = (char*)malloc(sizeof(char)*512);

	memory[3] = '\0';

	printf("\n\nBuffer content (before): %s.", memory);

	//alloc a region to put data read from disk
	read_disk_sector(memory, 32);

	memory[3] = '\0';

	printf("\n\nBuffer content (after): %s.", memory);
	
	printf("\n\nEnd of disk test.\n");
}

