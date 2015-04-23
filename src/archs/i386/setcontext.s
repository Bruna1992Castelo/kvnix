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

.code16gcc
.text

#include <minilib/ucontext.h>
#include <minilib/stddef.h>

#int setcontext(ucontext_t *)
.globl setcontext

setcontext:
    /* ucontext pointer */
    movl    4(%esp), %eax
 
    /* registers */
    mov     36(%eax), %bx
    mov     40(%eax), %cx
    mov     42(%eax), %dx
    mov     30(%eax), %si
    mov     32(%eax), %di

    /* stack pointers */
    mov     28(%eax), %ss 
    mov     4(%eax), %sp
    mov     8(%eax), %bp

    /* return position (CS:IP) */
    pushw   $0
    pushw   20(%eax)        #CS 
    pushw   $0
    pushw   22(%eax)        #IP 

    /* data segments */
    pushw   %bx
    pushw   %cx
    mov     24(%eax), %bx   #DS
    mov     26(%eax), %cx   #ES
    mov     %bx, %ds
    mov     %cx, %es
    popw    %cx
    popw    %bx
 
    /* flags */
    mov     32(%eax), %ax
    sahf
    
    /* AX = 0 */
    mov     $0, %ax

#loop:    jmp loop

    /* far returns pop the IP followed by the CS */
    lret

