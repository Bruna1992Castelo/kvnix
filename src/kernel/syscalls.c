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

#include <kvnix/syscalls.h>
#include <kvnix/callnr.h>
#include <minilib/string.h>

PUBLIC void syscall(int syscallnr, message *msgptr) {
	unsigned short ax;
	unsigned short bx;

	msgptr->m_type = syscallnr;

	//split msg address into two parts to be loaded onto registers ax, bx
	unsigned int pos = (unsigned int)msgptr;
	ax = (pos & 0x0000FFFF);
	bx = (pos >> 16);

	//call int 0x80, passing message 32-bit address
	__asm__(
			"int $0x80"
			:
			:"a"((unsigned short)ax), "b"((unsigned short)bx));
}

PUBLIC int open(const char *filename) {
    //TODO Open a file
}

PUBLIC int close(int fd) {
    //TODO Close a file
}
 
PUBLIC ssize_t read(int fd, void *buffer, size_t nbytes) {
	message msg;

	msg.m1_i1 = fd;
	msg.m1_p1 = buffer;
	msg.m1_i2 = nbytes;

	syscall(SYS_READ, &msg);

	return msg.m1_i3;
}

PUBLIC ssize_t write(int fd, void *buffer, size_t nbytes) {
	message msg;

	msg.m1_i1 = fd;
	msg.m1_p1 = (char *)buffer;
	msg.m1_i2 = nbytes;

	syscall(SYS_WRITE, &msg);

	return msg.m1_i3;
}

PUBLIC void load_program(const char *name) {
	message msg;

	msg.m1_p1 = name;
	msg.m1_i2 = strlen(name);

	syscall(SYS_LOAD_PROGRAM, &msg);
}

PUBLIC void sched_yield() {
	message msg;

	syscall(SYS_SCHED_YIELD, &msg);
}

PUBLIC int clone(int (*func)(void *), void *child_stack, size_t child_stack_size, void *arg)
{
    message msg;

    msg.m1_i1 = child_stack_size;

    syscall(SYS_CLONE, &msg);
    
    return msg.m1_i2;
}

PUBLIC int waitpid(int pid) {
    message msg;

	msg.m1_i1 = pid;
	
    syscall(SYS_WAIT_PID, &msg);

    return msg.m1_i2;
}

PUBLIC void exit(int exit_code) {
	message msg;

	msg.m1_i1 = exit_code;
	
    syscall(SYS_EXIT, &msg);
} 
