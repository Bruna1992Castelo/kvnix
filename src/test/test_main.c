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

#include <minilib/stdbool.h>
#include "test.h"
#include "string_test.c"
#include "tty_test.c"

void test_test1(test_case *tc) {
    test_assert(tc, true);
}

void test_test2(test_case *tc) {
    //nothing
}
 
void test_test3(test_case *tc) {
    test_assert(tc, false);
}
 
test_suite * create_auto_test()
{   
    test_suite *ts = create_test_suite("Auto Test");
    add_test_case(ts, "Pass Test", &test_test1);
    add_test_case(ts, "Not executed Test", &test_test2);
    add_test_case(ts, "Fail Test", &test_test3);
    
    return ts;
}

int main() {
    run_test_suite(create_auto_test());
    run_test_suite(create_string_test());
    run_test_suite(create_tty_test());
}


