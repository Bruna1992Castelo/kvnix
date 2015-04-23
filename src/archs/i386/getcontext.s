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

#int getcontext(ucontext_t *)
.globl getcontext

getcontext:
    pushl   %ebp
    movl    %esp, %ebp
    
    pushl   %ebx
    pushl   %ecx
    pushl   %edx

    /* ucontext pointer */
    movl    8(%ebp), %eax
 
    /* return position (CS:IP) */
    mov     4(%ebp), %bx    #get IP from the stack
    mov     %bx, 22(%eax)   #IP
    mov     %cs, 20(%eax)   #CS
 
    /* stack pointers */
    mov     %ss, 28(%eax) 
    mov     %bp, 4(%eax)    #SP (current BP is equals the original SP)
    mov     (%ebp), %bx     #BP (get the original BP from the stack)
    mov     %bx, 8(%eax)
 
    /* registers */
    mov     %ax, 34(%eax)
    mov     %bx, 36(%eax)
    mov     %cx, 40(%eax)
    mov     %dx, 42(%eax)
    mov     %si, 30(%eax)
    mov     %di, 32(%eax)

    /* data segments */
    mov     %ds, 24(%eax)   
    mov     %es, 26(%eax)   
 
    /* flags */
    pushl   %ebx            #store ebx
    movl    %eax, %ebx      #store ucontext pointer
    lahf                    #copy flags to AH
    xchg    %eax, %ebx      #EAX = ucontext pointer / EBX = flags
    mov     %bx, 32(%eax)   
    popl    %ebx            #restore ebx original value

    /* return value */
    mov     $0, %ax
    
    popl    %edx
    popl    %ecx
    popl    %ebx
    
    movl    %ebp, %esp 
    popl    %ebp
    
    ret

