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

#include <minilib/malloc.h>
#include <minilib/stdio.h>
#include <kvnix/syscalls.h>

void _start()
{
	puts("\nStarting Malloc Test");
	
    char* loc1 = (char*)malloc(sizeof(char)*5);

	if (loc1 == NULL)
		puts("\nUnable to allocate loc1.");
	else
		puts("\nLoc1 allocated with success.");

    loc1[0] = 'A';
    loc1[1] = 'B';
    loc1[2] = 'C';
    loc1[3] = 'D';
    loc1[4] = '\0';
   
	char* loc2 = (char*)malloc(sizeof(char)*5);

	if (loc2 == NULL)
		puts("\nUnable to allocate loc2.");
	else
		puts("\nLoc2 allocated with success.");

	loc2[0] = 'E';
	loc2[1] = 'F';
	loc2[2] = 'G';
	loc2[3] = 'H';
	loc2[4] = '\0';

	char* loc3 = (char*)malloc(sizeof(char)*5);

	if (loc3 == NULL)
		puts("\nUnable to allocate loc3.");
	else
		puts("\nLoc3 allocated with success.");

	loc3[0] = 'I';
	loc3[1] = 'J';
	loc3[2] = 'K';
	loc3[3] = 'L';
	loc3[4] = '\0';

	puts("\nRegion 1: ");
	puts(loc1);
	puts("\nRegion 2: ");
	puts(loc2);
	puts("\nRegion 3: ");
	puts(loc3);

	puts("\n\nStarting Realloc Test");

	loc2 = (char*)realloc(loc2, sizeof(char)*11);

	if (loc2 == NULL)
		puts("\nUnable to reallocate loc2.");
	else
		puts("\nLoc2 reallocated with success.");

	loc2[4] = ' ';
	loc2[5] = 'K';
	loc2[6] = 'V';
	loc2[7] = 'n';
	loc2[8] = 'i';
	loc2[9] = 'x';
	loc2[10] = '\0';

	puts("\nRegion 1: ");
	puts(loc1);
	puts("\nRegion 2 Reallocated: ");
	puts(loc2);
	puts("\nRegion 3: ");
	puts(loc3);

	puts("\n\nEnd of Tests.\n");

    free(loc1);
    free(loc2);
    free(loc3);

	exit(0);
}

