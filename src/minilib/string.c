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

#include <sys/types.h>
#include <minilib/string.h>
#include <archs/arch.h>    

PUBLIC void * memcpy(void *restrict to, const void *restrict from, size_t size) 
{
    if ((to == NULL) || (from == NULL)) {
        return NULL;
    }
    
    BYTE_COPY(to, from, size);

    return to;
}

PUBLIC void * memset(void *block, int c, size_t size) 
{
    if (block == NULL) {
        return NULL;
    }
    
	BYTE_SET(block, c, size);

    return block;
}

PUBLIC char * strcpy(char *restrict to, const char *restrict from) 
{
    size_t length = strlen(from);
    to[length] = '\0';

    return memcpy(to, from, length);
}

PUBLIC char * strncpy(char *restrict to, const char *restrict from, size_t size) 
{
    size_t length = strnlen(from, size);
    to[length] = '\0';

    return memcpy(to, from, length);
}

PUBLIC char * strcat(char *restrict to, const char *restrict from) 
{
    size_t to_length = strlen(to);
    size_t from_length = strlen(from);

    size_t total_length = to_length + from_length;

    to[total_length] = '\0';

    return memcpy(to + to_length, from, from_length);
}
 
PUBLIC char * strncat(char *restrict to, const char *restrict from, size_t size) 
{
    size_t to_length = strnlen(to, size);
    size_t from_length = strnlen(from, size - to_length);

    size_t total_length = to_length + from_length;

    to[total_length] = '\0';

    return memcpy(to + to_length, from, from_length);
}


PUBLIC size_t strlen(const char *str) 
{
    int i;
    for (i = 0; str[i] != '\0'; i++);

    return i * sizeof(char);
}

PUBLIC size_t strnlen(const char *str, size_t maxlen) 
{
    int i;
    for (i = 0; ((str[i] != '\0') && ((i * sizeof(char)) < maxlen)); i++);

    return i * sizeof(char);
}

PUBLIC int strcmp(const char *str1, const char *str2)
{
    int length1 = strlen(str1);
    int length2 = strlen(str2);

    int length = (length1 > length2) ? length1 : length2;
    
    for (int i = 0; i < length; i++) {
        int r = str1[i] - str2[i];

        if (r != 0) {
            return r;
        }
    }

    return 0;
}


