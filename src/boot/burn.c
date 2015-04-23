#include <stdio.h>
#include <string.h>
#include <sys/types.h> /* unistd.h needs this */
#include <unistd.h>    /* contains read/write */
#include <fcntl.h>

#define	SIZE 100*1024 //100KB

int main() {

	int pd, file_desc;
	char buffer[SIZE];

	//clean up
	memset(buffer, 0, SIZE);

	printf("\nReading Image...");

	//read SIZE bytes from image.bin
	file_desc = open("dist/image.bin", O_RDONLY);
    read(file_desc, buffer, SIZE);
    close(file_desc);
    
	printf("\nWriting Image...");

	//create a file with whole content
	pd = open("/dev/sdb", O_WRONLY|O_TRUNC);
	write(pd, buffer, SIZE);
	close(pd);

	printf("\nImage Burnt. :-) Enjoy it!\n\n");

	return 0;
}

