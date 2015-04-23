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

#include "test_ucontext.h"

#include <minilib/ucontext.h>
#include <minilib/stdio.h>
#include <minilib/stdlib.h>

__asm__(".code16gcc\n");


ucontext_t uc_main;
ucontext_t uc1;
ucontext_t uc2;

void c1() 
{
    for (int i = 0; i < 5; i++) {
        puts("Ping!\n");
    }

    swapcontext(&uc1, &uc_main);
}

void c2()
{
    for (int i = 0; i < 5; i++) {
        puts("  Pong!\n");
    } 
    
    swapcontext(&uc2, &uc_main);
}

void test_ucontext() 
{
	//Context 1
    getcontext(&uc1);
	
    uc1.uc_stack.ss_sp = malloc(500);
	uc1.uc_stack.ss_bp = uc1.uc_stack.ss_sp;
	uc1.uc_stack.ss_size = 500;
    
    makecontext(&uc1, &c1, 0);

    //Context 2
    getcontext(&uc2);
	
    uc2.uc_stack.ss_sp = malloc(500);
	uc2.uc_stack.ss_bp = uc1.uc_stack.ss_sp;
	uc2.uc_stack.ss_size = 500;
    
    makecontext(&uc2, &c2, 0); 
	
    //Context switching
    swapcontext(&uc_main, &uc1);
    swapcontext(&uc_main, &uc2);
}

