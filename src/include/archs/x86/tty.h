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

/**
 * @file
 *
 * Routines that use the BIOS interrupts to control the input from the keyboard
 * and the output to the screen.
 *
 * @author Klystofer Ortega
 * @author Victor V. Serta
 */

#ifndef _X86_TTY_H
#define _X86_TTY_H

/**
 * Max row number.
 */
#define TTY_MAX_ROW 24 //TODO Read this information in runtime.

/**
 * Max column number
 */ 
#define TTY_MAX_COLUMN 79  //TODO Read this information in runtime. 
 
/**
 * Initializes the tty through a BIOS routine call. 
 */
#define TTY_INIT()                                      \
     __asm__                                            \
            ("mov $0, %%ah   \n\t"                      \
             "mov $3, %%al   \n\t"                      \
             "int $0x10          "                      \
            :                                           \
            :                                           \
            :"cc"                                       \
            )                                           
 
/**
 * Clears the screen through a BIOS routine call.
 */
#define TTY_CLEAR_SCREEN()                              \
      __asm__                                           \
            ("mov $6, %%ah   \n\t"                      \
             "mov $0, %%al   \n\t"                      \
             "mov $7, %%bh   \n\t"                      \
             "mov $0, %%cx   \n\t"                      \
             "mov $0x184F, %%dx   \n\t"                 \
             "int $0x10          "                      \
            :                                           \
            :                                           \
            :"cc"                                       \
            )                                           


/**
 * Sets the cursor position through a BIOS routine call. 
 *
 * @param page page number
 * @param row row number
 * @param column column number
 */
#define TTY_SET_CURSOR_POSITION(page, row, column)      \
     __asm__                                            \
            ("#row                      \n\t"           \
             "mov %0, %%dh              \n\t"           \
             "                          \n\t"           \
             "#column                   \n\t"           \
             "mov %1, %%dl              \n\t"           \
             "                          \n\t"           \
             "#page                     \n\t"           \
             "mov %2, %%bh              \n\t"           \
             "                          \n\t"           \
             "#int 10h - 2nd service    \n\t"           \
             "mov $2, %%ah              \n\t"           \
             "int $0x10                     "           \
            :                                           \
            :"g" (row), "g" (column), "g" (page)        \
            :"cc"                                       \
            )                                           
/**
 * Prints a charachter through a BIOS routine call. 
 *
 * @param page page number
 * @param c character
 */ 
#define TTY_PRINT_CHAR(page, c)                         \
      __asm__                                           \
            ("#char                     \n\t"           \
             "mov %0, %%al              \n\t"           \
             "                          \n\t"           \
             "#page                     \n\t"           \
             "mov %1, %%bh              \n\t"           \
             "                          \n\t"           \
             "#int 10h - service 0Ah    \n\t"           \
             "mov $0x0A, %%ah           \n\t"           \
             "int $0x10                     "           \
            :                                           \
            :"g" (c), "g" (page), "c"(1)                \
            :"cc"                                       \
            )       
/**
 * Scrolls up the screen through a BIOS routine call. 
 */  
#define TTY_SCROLL_UP()                                 \
     __asm__                                            \
            ("mov $6, %%ah   \n\t"                      \
             "mov $1, %%al   \n\t"                      \
             "mov $7, %%bh   \n\t"                      \
             "mov $0, %%cx   \n\t"                      \
             "mov $0x184F, %%dx   \n\t"                 \
             "int $0x10          "                      \
            :                                           \
            :                                           \
            :"cc"                                       \
            )                                           
/**
 * Reads a charachter through a BIOS routine call. 
 *
 * @return character
 */  
#define TTY_READ_CHAR()                                 \
      __asm__                                           \
          ("#int 16h - service 0      \n\t"             \
           "mov $0, %%ah              \n\t"             \
           "int $0x16                 \n\t"             \
           "                          \n\t"             \
           "#get char                 \n\t"             \
           "mov %%al, %0                  "             \
          :"=g"(c)                                      \
          :                                             \
          :"cc"                                         \
          )                                             
 
#endif
