__asm__(".code16gcc");

#include "progs.h"

#define TEST_PROG_SIZE	10240

/**
 * Programs table written in disk.
 */
image_sect_t progs_table[NR_PROGS] = {
		{"dist/test_hello.bin"	, "test_hello"	, PROGS_BEGIN_POS					, 20},
		{"dist/test_input.bin"	, "test_input"	, PROGS_BEGIN_POS+TEST_PROG_SIZE*1	, 20}, 
		{"dist/test_output.bin"	, "test_output"	, PROGS_BEGIN_POS+TEST_PROG_SIZE*2	, 20}, 
		{"dist/test_malloc.bin"	, "test_malloc"	, PROGS_BEGIN_POS+TEST_PROG_SIZE*3	, 20},
		{"dist/test_string.bin"	, "test_string"	, PROGS_BEGIN_POS+TEST_PROG_SIZE*4	, 20} 
	};

