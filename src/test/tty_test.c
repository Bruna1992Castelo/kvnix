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

#include "../drivers/tty/tty.h"
#include "test.h"

#include <minilib/stdlib.h>
#include <archs/arch.h>


void test_print(test_case *tc);

void _start()
{
    test_print(NULL);
}


void test_print(test_case *tc) 
{
//    init_tty();
    clear_screen();

    set_cursor_position(0,0);
    print_char('A');
}

/*
test_suite * create_tty_test() {
    test_suite *ts = create_test_suite("TTY Test");
    
    add_test_case(ts, "print", &test_print);
    
    return ts;
} 
*/
