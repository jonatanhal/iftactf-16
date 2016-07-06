#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<err.h>

/*
 * So the idea here is to have a application act as a server
 * to which the extracted client can connect to and request
 * a flag.
 * The client connects and sends a encrypted message, which
 * we verify, and return a flag in cleartext.
 *
 * For a bonus challenge, make the server vulnerable to some
 * exploit, (hidden 'debug' mode?)
 */

#define size 64

void
get_flag()
{
	int fh;
	char buffer[256];
	
	fh = open("/home/forensics100/flag.txt", O_RDONLY);
	if (fh == -1) {
		errx(1, "%s\n", strerror(errno));
	}

	read(fh, buffer, sizeof(buffer));

	printf("Nicely done! Here's your flag: %s\n", buffer);
}

int
main()
{
	const int offset = 0x1337;
	int i, keyfh;
	unsigned char input[size];
	unsigned char key[size];
	unsigned char cmd[4];
	unsigned int inputSize;

	keyfh = open("/home/forensics100/forensics100.jpg", O_RDONLY);
	if (keyfh == -1) {
		errx(1, "%s\n", strerror(errno));
	}
	lseek(keyfh, offset, SEEK_SET);
	read(keyfh, key, size);
	close(keyfh); 

	fread(&inputSize, 4, 1, stdin);
	fread(input, 1, size, stdin);
	fread(cmd, 1, 4, stdin);

	// debug stuff:
	/* fwrite(&inputSize, 4, 1, stdout); */
	/* fwrite(input, 1, size, stdout); */
	/* fwrite(cmd, 1, 4, stdout); */

	if (memcmp(key, input, size) == 0)
	{
		if (strncmp("flag", cmd, 4) == 0) 
			get_flag();
		if (strncmp("dbug", cmd, 4) == 0)
			puts("not implemented");
	}  else { 
	 	puts("Stop trying to hack me"); 
	} 
}
