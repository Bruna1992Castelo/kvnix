#include <stdio.h>
#include <string.h>
#include <sys/types.h> /* unistd.h needs this */
#include <fcntl.h>
#include "../commands/shell/progs.h"
#include <malloc.h>

#define NR_SECTORS	3

//Kernel Image Sectors
image_sect_t sects[NR_SECTORS] = {
		{"dist/preboot.bin"	, NULL, 0x0000,  1},	//PreBootloader
		{"dist/boot.bin"	, NULL, 0x0200,  1},	//Bootloader
		{"dist/kvnix.bin"	, NULL, 0x0400, 60} 	//Kernel
	};


int main() {

	int pd, file_desc, i;
	unsigned int size;
	char * buffer;

	pd = open("dist/image.bin", O_WRONLY|O_TRUNC|O_CREAT, 666);

	//kernel
	for (i=0; i < NR_SECTORS; i++) {
		
		printf("\nReading %s [Start %ld]...", sects[i].filename, sects[i].start);
		
		size = sects[i].nrsects*512;
		buffer = (char *)malloc(size);
		memset(buffer, 0, size);

		//file content	
		file_desc = open(sects[i].filename, O_RDONLY);
    	read(file_desc, buffer, size);
    	close(file_desc);

		lseek(pd, sects[i].start, SEEK_SET);
		write(pd, buffer, size);

		free(buffer);
    }

	//programs
	for (i=0; i < NR_PROGS; i++) {

		printf("\nReading %s [Start %ld]...", progs_table[i].filename, progs_table[i].start);
		
		size = progs_table[i].nrsects*512;
		buffer = (char *)malloc(size);
		memset(buffer, 0, size);
		
		file_desc = open(progs_table[i].filename, O_RDONLY);
    	read(file_desc, buffer, size);
    	close(file_desc);

		lseek(pd, progs_table[i].start, SEEK_SET);
		write(pd, buffer, size);

		free(buffer);
    }

	close(pd);

	printf("\nImage Created. :-) Enjoy it!\n\n");

	return 0;
}

