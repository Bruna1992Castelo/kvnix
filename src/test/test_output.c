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
#include <kvnix/syscalls.h>

void _start()
{
	putchar('T');
	putchar('\n');
	putchar('E');
	putchar('\n');
	putchar('S');
	putchar('\n');
	putchar('T');
	putchar('\n');

	puts("\nPuts test...\n");

	char *s1 = "KVnix";
	char *s2 = "Operating System";

	printf("\n%s %i\n%s.", s1, 2009, s2);

	puts("\n\nEnd of Tests.\n");

	exit(0);
}

