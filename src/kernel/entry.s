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

.code16
.text

#include "../include/kvnix/ints.h"

.globl _init_interrupt, _system_call, _init_timer, _stop_timer

# Initialize IVT (Start at 0000:0000)
# Each entry takes 4 bytes (Total 1KB)
_init_interrupt:
	cli
	movw	$0x0000, %ax		
	leaw	_system_call, %bx	#functions address
	movw	$0x0000, %di		#ivt base address
	movw	%bx, 0x200(%di)		#int 0x80
	movw	%ax, 0x202(%di)
	sti
	ret

# Entry routine for system calls
# AX, BX holds 32-bit address (message *)
_system_call:
	movw	%ss, %dx	# keep old stack segment
	movw	$0 , %cx
	movw	%cx, %ss	# kernel stack

	pushw	%dx			#save registers
	pushw	%es
	pushw	%ds
	pushw	%fs
	pushw	%sp
	pushw	%bp

	pushw	$0
	pushw	%ds			#param3
	pushw	$0
	pushw	%bx			#param2
	pushw	$0
	pushw	%ax			#param1

	movw	$0, %cx		#return ds to kernel space
	movw	%cx, %ds

	pushw	$0			#used to keep compatibility with 32-bit stack
    sti


	call handle_int

	addw	$12, %sp	#removing functions parameters from stack

	popw	%bp			#restore registers
	popw	%sp
	popw	%fs
	popw	%ds
	popw	%es
	popw	%ss

	iret

# Initialize Timer Interruption
_init_timer:
	movw	$0, %ax
	leaw	_timer_int, %bx
	movw	$0, %di
	movw	%bx, 0x70(%di)		# 1Ch
	movw	%ax, 0x72(%di)
	ret

# Disable Timer Interruption
_stop_timer:
	movw	$0xab7a, %bx
	movw	$0xf000, %ax
	movw	$0, %di
	movw	%bx, 0x70(%di)		# 1Ch
	movw	%ax, 0x72(%di)
	ret

# Routine to treat timer interruptions
_timer_int:
	movw	%ss, %dx	# keep old stack segment
	movw	$0 , %cx
	movw	%cx, %ss	# kernel stack

	pushw	%dx			#save registers
	pushw	%es
	pushw	%ds
	pushw	%fs
	pushw	%sp
	pushw	%bp

	movw	$0, %cx		#return DS to kernel space
	movw	%cx, %ds

	pushw	$0			#used to keep compatibility with 32-bit stack
	call	timer_int

	popw	%bp			#restore registers
	popw	%sp
	popw	%fs
	popw	%ds
	popw	%es
	popw	%ss
	
	iret

