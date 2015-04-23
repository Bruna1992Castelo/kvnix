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

#int swapcontext(ucontext_t * restrict oucp, const ucontext_t * restrict ucp)            
.globl swapcontext

swapcontext:
    pushl   %ebp
    movl    %esp, %ebp

    pushl   %ebx
    pushl   %ecx
    pushl   %edx

    /* params */
    movl    8(%ebp), %eax       #old ucontext pointer
    movl    12(%ebp), %edx      #new ucontext pointer

    /* get old context */
    pushl   %eax
    call   getcontext
    popl    %eax
    
    /* instruction pointer redefinition */
    movl    $oldcontext_return, %ebx
    movw    %bx, 22(%eax)          #IP 
    
    /* set new context */
    subl   $8, %esp
    movl   %edx, (%esp)
    call   setcontext

oldcontext_return:
    popl    %eax                #when getcontext() was called, eax had popped to the stack
    movl    $0, %eax

    popl    %edx
    popl    %ecx
    popl    %ebx
    
    movl    %ebp, %esp
    popl    %ebp
    ret
