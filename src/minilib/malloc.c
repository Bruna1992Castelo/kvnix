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

#include <minilib/malloc.h>
#include <kvnix/syscalls.h>
#include <kvnix/callnr.h>
#include <ipc/ipc.h>

__asm__(".code16gcc\n");

PUBLIC void * malloc(size_t size) {
	message msg;

	msg.m1_i1 = (int)size;

	syscall(SYS_MALLOC, &msg);

	return (void *)msg.m1_p1;
}

PUBLIC void free(void* pointer) {
	message msg;

	msg.m1_p1 = (char *)pointer;

	syscall(SYS_FREE, &msg);
}

PUBLIC void * realloc(void* pointer, size_t size) {
	message msg;

	msg.m1_i1 = (int)size;
	msg.m1_p1 = (char *)pointer;

	syscall(SYS_REALLOC, &msg);

	return (void *)msg.m1_p2;
}

