#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	FILE *fd = fopen("/dev/ttyUSB1", "ab");
	if( !fd )
	{
		perror("can't open device file\n");
		return 1;
	}
	char buffer[5];
	int action = atoi(argv[1]);
	if( action == 0 )
	{
		// write 8 bit register
		buffer[0] = 0;
		// address
		buffer[1] = (char)strtol(argv[2], NULL, 16);
		// value
		buffer[2] = (char)strtol(argv[3], NULL, 16);
		fwrite(buffer, 5, 1, fd);
	}
	else if( action == 1 )
	{
		// write 16 bit register
		buffer[0] = 1;
		// address
		buffer[1] = (char)strtol(argv[2], NULL, 16);

		uint16_t v = (uint16_t)strtol(argv[3], NULL, 16);
		buffer[2] = (char)(v);
		buffer[3] = (char)(v>>8);
		fwrite(buffer, 5, 1, fd);
	}
	else if( action == 2 )
	{
		// read 8 bit register
		buffer[0] = 2;
		// address
		buffer[1] = (char)strtol(argv[2], NULL, 16);
		fwrite(buffer, 5, 1, fd);
		fflush(fd);
		char data;
		sleep(1);
		printf("read count %d\n", fread(&data, 1, 1, fd));

		printf("read data %X\n", data);

	}
	else if( action == 3 )
	{
		// read 16 bit register
		buffer[0] = 3;
		// address
		buffer[1] = (char)strtol(argv[2], NULL, 16);
		fwrite(buffer, 5, 1, fd);
		fflush(fd);
		char data[2];
		sleep(1);
		printf("read count %d \n", fread(data, 1, 2, fd));
		printf(" data : %X %X\n", data[0], data[2]);

	}
	fclose(fd);
	return 0;
}
