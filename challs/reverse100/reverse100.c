#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

#define size 48

const char hint[] = "%s is not the signal we're looking for...\n";

void
decrypt_flag()
{
	int i;
	const char key[] = {
		0x4f, 0x0a, 0x99, 0xb1, 0x39, 0x4f, 0x34,
		0x3d, 0x39, 0x23, 0xc5, 0xe3, 0x2f, 0x91,
		0x71, 0x35, 0xe1, 0x2c, 0xa1, 0xc8, 0x6c,
		0xe5, 0x3d, 0x59, 0x5f, 0x54, 0xb0, 0xb2,
		0xbd, 0xa8, 0x97, 0x2c, 0x38, 0x09, 0xeb,
		0xe8, 0x8f, 0xe6, 0x3f, 0xb0, 0x58, 0xb6,
		0x2c, 0x1d, 0x4f, 0xd0, 0xae, 0x00
	};
	const char eflag[] = {
		0x26, 0x6c, 0xed, 0xd0, 0x5a, 0x3b, 0x52,
		0x0c, 0x0f, 0x58, 0xf1, 0x85, 0x4c, 0xa4,
		0x15, 0x51, 0xd8, 0x1b, 0x8c, 0xfb, 0x58,
		0xdc, 0x5c, 0x74, 0x6b, 0x35, 0x84, 0x87,
		0x90, 0xc9, 0xae, 0x48, 0x5a, 0x24, 0xd3,
		0x8c, 0xbf, 0x85, 0x0a, 0x83, 0x39, 0xd5,
		0x18, 0x24, 0x2d, 0xe9, 0xd3, 0x00
	};
	
	char *decrypt, *pointer;

	decrypt = calloc(1, size);
	if (decrypt == NULL) {
		puts("Unable to allocate memory, contact admins please");
		exit(1);
	}
	pointer = decrypt;
	
	for (i = 0; i < size; i++)
	{
		*(pointer) = eflag[i] ^ key[i];
		pointer++;
	}
	puts(decrypt);
	free(decrypt);
}

void
handler(int sig)
{
	switch(sig) {
	case SIGUSR1:
		decrypt_flag();
		break;
	}
}

int
main(int argc, char **argv)
{
	signal(SIGUSR1, handler);

	while(1)
	{
		sleep(1);
	}
	return 0;
}




