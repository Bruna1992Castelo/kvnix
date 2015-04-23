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

#include "tty.h"
#include <archs/arch.h>

__asm__(".code16gcc\n");

void tty_test()
{

    tty_clear_screen();
    
    tty_init();
    
    tty_print_char('A');
    tty_print_char('B');
    tty_print_char('C');
    tty_print_char('\n');
    tty_print_char('D');
    tty_print_char('E');
    tty_print_char('F');
    tty_print_char('\n');
    tty_print_char('G');
    tty_print_char('H');
    tty_print_char('I');
    tty_print_char('\n');
    tty_print_char('J');
    tty_print_char('K');
    tty_print_char('L');

    while (1) {
        char c = tty_read_char();
        tty_print_char(c);
    }
}
 

PUBLIC void tty_init()
{
    TTY_INIT();

    console.max_row = TTY_MAX_ROW;
    console.max_column = TTY_MAX_COLUMN;
    
    tty_set_cursor_position(0,0);
}


PUBLIC void tty_clear_screen()
{
    TTY_CLEAR_SCREEN();
    tty_set_cursor_position(0,0);
}


PUBLIC void tty_set_cursor_position(int row, int column)
{
	if (column < 0)
		column = 0;

	if (row < 0)
		row = 0;

    if (column >= console.max_column) {
        row++;
        column = 0;
    }

    if (row >= console.max_row) {
        TTY_SCROLL_UP();
        row = console.max_row - 1;
    }

    TTY_SET_CURSOR_POSITION(0, row, column);

    console.cursor_row = row;
    console.cursor_column = column;
}

PUBLIC void tty_print_char(char c)
{                                        
    int new_cursor_row = console.cursor_row;
    int new_cursor_column = console.cursor_column;
    
    switch (c) {
        case '\n':
            new_cursor_row++;
        case '\r':
            new_cursor_column = 0;
            break;
		case '\b':
			new_cursor_column--;
    		tty_set_cursor_position(new_cursor_row, new_cursor_column);

			TTY_PRINT_CHAR(0, ' ');

			break;
        default:
            TTY_PRINT_CHAR(0, c);
            new_cursor_column++;
    }

    tty_set_cursor_position(new_cursor_row, new_cursor_column);
}

PUBLIC char tty_read_char()
{
    char c;
    TTY_READ_CHAR();

    switch (c) {
        //FIXME Put it on file of specific architecture 
        case 13:
            c = '\n';
            break;
        //default:
            //tty_print_char(c);
    }

    return c;
}



