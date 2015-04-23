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

#include <minilib/stdio.h>
#include <minilib/malloc.h>
#include <kvnix/syscalls.h>

#define SIZE (sizeof(char) * 50)

void _start()
{
	char c = 0;
	char *text = (char*)malloc(SIZE);

	puts("\nType a key: ");
	c = (char)getchar();

	puts("\nYou typed ");
	putchar((int)c);	

    size_t size = SIZE;

	puts("\nEnter a string: ");
	getline(&text, &size, stdin);

	puts("\nYou entered: ");
	puts(text);
	
	puts("\n\nEnd of Tests.\n");

	exit(0);
}

