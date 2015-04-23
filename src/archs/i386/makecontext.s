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

#void makecontext(ucontext_t *, void (*func)(void), int argc, ...)
.globl makecontext

makecontext:
    pushl   %ebp
    movl    %esp, %ebp

    /* params */
    movl    8(%ebp), %eax       #ucontext pointer
    movl    12(%ebp), %edx      #function

    /* instruction pointer redefinition */
    movw    %dx, 22(%eax)      #IP

    /* stack base */
    movl    4(%eax), %ebx       #SP
    movl    12(%eax), %edx      #stack size
    addl    %edx, %ebx
    decl    %edx
    movl    %ebx, 4(%eax)       #new SP

    movl    %ebp, %esp
    popl    %ebp

    ret

