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

#include <kvnix/util.h>
#include <minilib/stdio.h>
#include <minilib/string.h>

PUBLIC void panic(char *module, char *message)
{
    if (module == NULL) {
        module = "Kvnix";
    }
   
	do_write(1, "\n\nPANIC => ", 11);
	do_write(1, module, strlen(module));
	do_write(1, ": ", 2);
	do_write(1, message, strlen(message));
 
	while (1);
}
