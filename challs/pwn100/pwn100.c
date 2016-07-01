#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <error.h>
#include <errno.h>

void
get_flag()
{
	int fh;
	char buffer[256];
	
	fh = open("/home/pwn100/flag.txt", O_RDONLY);
	if (fh == -1) {
		errx(1, strerror(errno));
	}

	read(fh, buffer, sizeof(buffer));

	printf("Nicely done! Here's your flag: %s\n", buffer);
}

int
main(int argc, char **argv)
{
	char *secretPassword = "n0on3_w1ll_b3_abl3_t0_gu3s5_th1s";
	long returnaddr;
	char buffer[128];
	puts("Input the magic string and recieve a flag: ");
	gets(buffer);
	if (strlen(buffer) > 128) {
		puts("!! HACKER DETECTED !!");
	} else {
		puts("Good guess, but you're wrong");
	}
	strcmp(buffer, secretPassword);

	returnaddr = __builtin_return_address(0);
	printf("Saved Return Address: %p\n", (void *) returnaddr);
	return 0;
}
