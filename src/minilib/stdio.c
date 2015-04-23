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

#include <minilib/stdio.h>
#include <minilib/stdlib.h>
#include <minilib/stdbool.h>
#include <minilib/string.h>
#include <kvnix/syscalls.h>
#include <kvnix/util.h>
#include <minilib/malloc.h>
#include <stdarg.h>

__asm__(".code16gcc\n");

FILE * stdin;
FILE * stdout;
FILE * stderr;

PUBLIC FILE* fdopen(int fd)
{
    //TODO Implement fdopen
    return NULL;
}
 
PUBLIC FILE* fopen(const char *filename)
{
    //TODO Implement fopen
    return NULL;
}
 
PUBLIC void fclose(FILE *stream)
{
    //TODO Implement fclose
}

PUBLIC int fputc(int c, FILE *stream)
{
	char str[2];
	str[0] = c;
	str[1] = '\0';

    return write(1, str, 1);
}
 
PUBLIC int putchar(int c)
{
    return fputc(c, NULL);
}

PUBLIC int fgetc(FILE *stream)
{
    char str[1];
    int r = read(0, str, 1);

    if (r < 0) {
        return r;
    }

    return str[0];
}

PUBLIC int getchar()
{
    return fgetc(NULL);
}
 
PUBLIC int fputs(const char *str, FILE *stream)
{
    return write(1, (void*)str, strlen(str));    
}
 
PUBLIC int puts(const char *str)
{
    return fputs(str, NULL);
}

PUBLIC int fprintf(FILE *stream, const char *template, ...)
{
    //TODO Implement fprintf

    return fputs(template, stream);
}

PUBLIC int printf(const char *format, ...)
{
	const char *p;
    char *a1, *tmp_conv;
	int a2;
    char a3;
	va_list list;

    int size = 0;

	//temporary region for int conversion
	tmp_conv = (char *)malloc(sizeof(char)*50);
    
	if (tmp_conv == NULL) {
        return -1;
    }

	//prepare list for va_arg
	va_start(list, format);

	for (p=format; *p; p++)	{

		if (*p == '%') {

			switch (*++p) {

				/* string */
				case 's':
					a1 = va_arg(list, char *);
					size += puts(a1);

					break;

 				/* integer */
                case 'd':
				case 'i':
					a2 = va_arg(list, int);
					itoa(a2, tmp_conv, 10);
					size += puts(tmp_conv);

					break;

                case 'c':
                    a3 = va_arg(list, int);
                    putchar(a3);
                    size++;

                    break;

				default:
					putchar(*p);
                    size++;
			}
		} else {
			putchar((int)*p);
            size++;
		}
	}
	
	va_end(list);

	free(tmp_conv);
	
	return size;
}

PUBLIC char *gets(char *s)
{
	int p = 0;
	s[0] = '\0';

	char c = 0;

	do {
		c = getchar();

		switch (c) {
			case '\b':
				if (p > 0)
				{
					s[--p] = '\0';
					putchar('\b');
				}
				break;
			case '\n':
				putchar('\n');
				break;
			default:
				s[p++] = c;
				s[p] = '\0';
				putchar(c);
		}

	} while (c != EOF && c != '\n');

	return s;
}

PUBLIC ssize_t getline(char **lineptr, size_t *sizeptr, FILE *stream)
{
    size_t pos = 0;
    
    int c = 0;
    char *s = *lineptr;
	
    s[0] = '\0';

    //repeats until end-of-file or new line are not found
    do {
        if (((pos + 1) * sizeof(char)) >= *sizeptr) {
            //ops... we need to allocate more memory
            *sizeptr = sizeof(char) * (pos + 10);
            *lineptr = realloc(*lineptr, *sizeptr);
            s = *lineptr;
        }
        
        c = fgetc(stream);

		switch (c) {
			case '\b':
				if (pos > 0) {
					s[--pos] = '\0';
					putchar('\b');
                }
				break;
            case '\n':
                break;
			default:
				s[pos++] = c;
				s[pos] = '\0';
				putchar(c);
		}
	} while (c != EOF && c != '\n');

    return pos;
}

