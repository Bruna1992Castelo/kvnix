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
 * Functions to print/read to/from streams or the screen/keyboard.
 *
 * They are used by the system instead of libc (stdio.h) to mantain the operating
 * system code more simple.
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <util/code_const.h>
#include <minilib/stddef.h>

/**
 * File descriptor for standard input.
 * The value of the file descriptor for stantard input is 0.
 */
#define STDIN_FILENO 0

/**
 * File descriptor for standard output.
 * The value of the file descriptor for stantard output is 1.
 */
#define STDOUT_FILENO 1

/**
 * File descriptor for standard error output.
 * The value of the file descriptor for stantard error output is 2.
 */
#define STDERR_FILENO 2 

/**
 * End of file.
 */
#define EOF -1

/**
 * File stream for a file descriptor.
 */
typedef struct FILE {
    /**
     * File descriptor of the file stream.
     */
    int fd;

} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;


/**
 * Opens a file stream for I/O to the file descriptor.
 *
 * @param fd filedescriptor
 */
PUBLIC FILE* fdopen(int fd);
 
/**
 * Opens a file stream for I/O to the file of filename.
 *
 * @param filename name of the file
 */
PUBLIC FILE* fopen(const char *filename);
 
/**
 * Closes a file stream.
 *
 * @param stream to close
 */
PUBLIC void fclose(FILE *stream);

/**
 * Writes the character c to stream.
 *
 * @param c the character
 * @param stream destination
 * @return character c or EOF if an error occurs
 */
PUBLIC int fputc(int c, FILE *stream);
 
/**
 * Writes the char c to stream stdout.
 *
 * @param c the character
 * @return character c or EOF if an error occurs
 */
PUBLIC int putchar(int c);

/**
 * Reads the next character from the stream. If an end-of-file is
 * found, it returns EOF.
 *
 * @param stram origin
 * @return character read or EOF if an error or end-of-file occurs
 */
PUBLIC int fgetc(FILE *stream);

/**
 * Reads the next character from the stream stdin. If an end-of-file is
 * found, it returns EOF.
 *
 * @return the character read or EOF if an error or end-of-file occurs
 */
PUBLIC int getchar();

/**
 * Prints the string to stream.
 *
 * @param str the string
 * @param stream destination
 * @return number of characters written or EOF if an error occurs
 */
PUBLIC int fputs(const char *str, FILE *stream);

/**
 * Prints the string to stream stdout.
 *
 * @param the string
 * @return number of characters written or EOF if an error occurs
 */
PUBLIC int puts(const char *str);

/**
 * Prints the template string replacing the arguments to stream.
 *
 * @param stream destination
 * @param template template string
 * @return number of characters written or EOF if an error occurs
 */
PUBLIC int fprintf(FILE *stream, const char *template, ...);

/**
 * Prints the template string replacing the arguments to stream stdout.
 *
 * @param template template string
 * @return number of characters written or EOF if an error occurs
 */
PUBLIC int printf(const char *template, ...);

/**
 * Read a line from the standard input.
 */
PUBLIC char *gets(char *s);

/**
 * Reads a line from the stream. If the line size is greater than the 
 * allocated in sizeptr then malloc() is called. It changes the value
 * of *lineptr and sizeptr.
 *
 * @param lineptr pointer to line
 * @param sizeptr poiter to line size
 * @param stream origin
 */
PUBLIC ssize_t getline(char **lineptr, size_t *sizeptr, FILE *stream);
  
#endif
