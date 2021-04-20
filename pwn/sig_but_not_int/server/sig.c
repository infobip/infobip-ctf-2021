#include <stdio.h>
#include <stdlib.h>

void am() {
	__asm__("pop %rax; syscall; ret;");
}

void banner() {
	char buff[100];
	printf("Delete most of the code and you are secure, right? (Y/n) ");
	read(0, buff, 1024);
}

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	banner();
	return 0;
}
