#include<stdio.h>

int main()
{
	char buffer[512];
	printf("buffer is at %p\ncan you gain control?\n", &buffer);
	gets(buffer);
}
