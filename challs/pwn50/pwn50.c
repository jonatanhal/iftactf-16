#include<stdio.h>
#include<errno.h>
#include<error.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define size 256

void get_flag();
int change_me = 0;

int
main()
{
	char input[size];
	printf("Your input: %s\n", input);
	fgets(input, size, stdin);
	printf(input);
	if (change_me) {
		get_flag();
	}
	return 0;
}

void
get_flag()
{
	int fh;
	char buffer[size];
	
	fh = open("/home/pwn50/flag.txt", O_RDONLY);
	if (fh == -1) {
		errx(1, strerror(errno));
	}

	read(fh, buffer, size);

	printf("Nicely done! Here's your flag: %s\n", buffer);
}
