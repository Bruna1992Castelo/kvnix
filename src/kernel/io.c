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

#include <kvnix/io.h>
#include "../drivers/tty/tty.h"

PUBLIC ssize_t do_read(int fd, void *buffer, size_t nbytes)
{
    //TODO Read from files

    if (fd != 0) {
        return -1;
    }

    char *str = buffer;
    size_t i = 0;

    for (size_t i = 0; i < nbytes; i++) {
        str[i] = tty_read_char();
    }

    return i;
}
 
PUBLIC ssize_t do_write(int fd, void *buffer, size_t nbytes)
{
    //TODO: Write to files
    char *str = buffer;
	int i;

    for (i = 0; i < nbytes; i++)
	   	tty_print_char(str[i]);

    return i;
} 

