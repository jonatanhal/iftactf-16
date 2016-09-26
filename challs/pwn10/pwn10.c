#include<fcntl.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<err.h>
#include<string.h>
#include<errno.h>

#define size 512

void
get_flag()
{
	int fh;
	char buffer[size];
	
	fh = open("/home/pwn25/flag.txt", O_RDONLY);
	if (fh == -1) {
	  errx(1, "%s\n", strerror(errno));
	}

	read(fh, buffer, size);

	printf("Are you a hacker or something??? Here's your flag: %s\n", buffer);
	close(fh);
}

int
main(void)
{
  volatile int mod;
  char guess[32];

  mod = 0;
  puts("Enter the magic passphrase:");
  gets(guess);

  if (mod)
    get_flag();
  else
    puts("Wrong! :(");
  exit(0);
}
