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

#include <minilib/stdlib.h>
#include <minilib/stdio.h>
#include <minilib/string.h>
#include <kvnix/syscalls.h>

void test_str_mem();
void test_str_cpy();
void test_str_concat();
void test_str_length();
void test_str_cmp();

void _start()
{
    puts("\nStarting String Tests\n");

    test_str_mem();
    test_str_cpy();
    test_str_concat();
    test_str_length();
    test_str_cmp();

    puts("\nEnd of Tests.");

	exit(0);
}

void test_str_mem()
{
    char *a = malloc(sizeof(char) * 26);
    char *b = malloc(sizeof(char) * 26);

    for (int i = 0; i < 25; i++) {
        a[i] = i + 65;
    }

    a[25] = 0;
    b[25] = 0;
    
    printf("Before memset(): a=\"%s\" | b=\"%s\"\n", a, b);
    memset(b, '0', 25);
    printf("After memset(): a=\"%s\" | b=\"%s\"\n", a, b);

    memcpy(a, b, 25);
    printf("After memcpy(): a=\"%s\" | b=\"%s\"\n\n", a, b);

    free(a);
    free(b);
}


void test_str_cpy() 
{
    const char *a = "Hello world!";
    char *b = malloc(sizeof(char) * 6);
    char *c = malloc(sizeof(char) * 14);
    
    b[0] = 0;
    c[0] = 0;

    strncpy(b, a, 5);
    strcpy(c, a);

    printf("String: \"%s\"\n", a);
    printf("strncpy(to, from, 5): \"%s\"\n", b);
    printf("strcpy(to, from): \"%s\"\n\n", c);

    free(b);
    free(c);
}

void test_str_concat()
{
    const char *nixOS = "nixOS";
    const char *kv = "KV";

    char *result1 = malloc(sizeof(char) * 6);
    char *result2 = malloc(sizeof(char) * 8);

    result1[0] = 0;
    result2[0] = 0;

    strcpy(result1, kv);
    strncat(result1, nixOS, 5);
   
    strcpy(result2, kv);
    strcat(result2, nixOS);

	result2[7] = '\0';

    printf("strncat(\"%s\", \"%s\", 3): '%s'\n", kv, nixOS, result1);
    printf("strcat(\"%s\", \"%s\"): '%s'\n\n", kv, nixOS, result2);
}

void test_str_length()
{
    const char *str = "Hello world!";

    int nlen1 = strnlen(str, 5);
    int nlen2 = strnlen(str, 50);
    int len = strlen(str);

    printf("strnlen(\"%s\", 5): %d\n", str, nlen1);
    printf("strnlen(\"%s\", 50): %d\n", str, nlen2);
    printf("strlen(\"%s\"): %d\n\n", str, len);
}

void test_str_cmp()
{
    const char *brasil1 = "Brasil";
    const char *brasil2 = "Brasil";
    const char *brazil = "Brazil";

    int result1 = strcmp(brasil1, brasil2);
    int result2 = strcmp(brasil1, brazil);

    printf("strcmp(\"%s\", \"%s\"): %d\n", brasil1, brasil2, result1);
    printf("strcmp(\"%s\", \"%s\"): %d\n", brasil1, brazil, result2);
}

