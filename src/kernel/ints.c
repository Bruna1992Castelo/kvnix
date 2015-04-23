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

#include <kvnix/ints.h>

#include <sys/types.h>

#include <ipc/ipc.h>
#include <kvnix/callnr.h>
#include <kvnix/syscalls.h>
#include <kvnix/io.h>
#include <kvnix/clock.h>
#include <kvnix/mm/alloc.h>
#include <kvnix/pm/pm.h>
#include <kvnix/pm/sched.h>
#include <archs/x86/regs.h>
#include <kvnix/util.h>

#include "../drivers/tty/tty.h"

#define INT_NAME "Interruption"

/**
 * Copy data from the specified segment.
 */
void *copy_from_other_segment(unsigned short seg, unsigned short offset, unsigned short count);

/**
 * Copy data to the specified segment.
 */
void copy_to_other_segment(unsigned short data, unsigned short seg, unsigned short offset, unsigned short count);


void *copy_from_other_segment(unsigned short seg, unsigned short offset, unsigned short count) 
{
	void *data = kmalloc(count + 20);
	if (data == NULL)
		panic(INT_NAME, "Unable to allocate memory at copy_from_other_segment().");

	unsigned short to_seg = 0;

	BYTE_COPY2(to_seg, data, seg, offset, count);

	return data;
}

void copy_to_other_segment(unsigned short data, unsigned short seg, unsigned short offset, unsigned short count) 
{
	unsigned short from_seg = 0;

	BYTE_COPY2(seg, offset, from_seg, data,  count);
}


void handle_int(unsigned short ax, unsigned short bx, unsigned short ds) 
{
	enable_preemption(false);
	
	void *arg;

	unsigned int pos = bx;
	pos = pos << 16;
	pos += ax;

	message *msgptr = (message *)copy_from_other_segment(ds, (unsigned short)pos, sizeof(message));

	unsigned int seg = 0;

	//call specific syscall function, according to m_type parameter
	switch (msgptr->m_type) {
        case SYS_EXIT:
			do_exit(msgptr->m1_i1);
			break;                         

		case SYS_READ:	
			arg = copy_from_other_segment(ds, msgptr->m1_p1, msgptr->m1_i2);
			msgptr->m1_i3 = do_read(msgptr->m1_i1, arg, (size_t)msgptr->m1_i2);	

			copy_to_other_segment(arg, ds, msgptr->m1_p1, msgptr->m1_i2);

			kfree(arg);
			break;

		case SYS_WRITE:
			arg = copy_from_other_segment(ds, msgptr->m1_p1, msgptr->m1_i2);
			msgptr->m1_i3 = do_write(msgptr->m1_i1, arg, (size_t)msgptr->m1_i2);

			kfree(arg);

			break;

        case SYS_WAIT_PID:
			do_waitpid(msgptr->m1_i1);
			break;                         

		case SYS_MALLOC:
			msgptr->m1_p1 = do_malloc(msgptr->m1_i1);
			break;

		case SYS_FREE:
			do_free(msgptr->m1_p1);
			break;

		case SYS_REALLOC:
			msgptr->m1_p2 = (char *)do_realloc((void *)msgptr->m1_p1, msgptr->m1_i1);
			break;

		case SYS_LOAD_PROGRAM:
			arg = copy_from_other_segment(ds, msgptr->m1_p1, msgptr->m1_i2);

			do_load_program(arg);
			break;
 
        case SYS_CLONE:
			msgptr->m1_i2 = do_clone(msgptr->m1_p1, msgptr->m1_p2, (size_t) msgptr->m1_i1, msgptr->m1_p3);
			break;            

		case SYS_SCHED_YIELD:
			task_yield();
			break;
	}

	int size = sizeof(message);
	copy_to_other_segment(msgptr, ds, pos, size);

	kfree(msgptr);
	
	enable_preemption(true);
}

void timer_int() 
{
    handle_clock_tick();
}

