#include <stdio.h>
#include <stdlib.h>

void printf_wrapper(char* m) {
	printf("%s\n", m);
}

void start() {
	char test_input[100];
	char* warn = "Still in development, but you can input something";
	char* msg = "This is all you need, I guarantee it.";
	printf_wrapper(warn);
	printf("printf %p\n", printf);
	printf_wrapper(msg);
	scanf("%s", test_input);
}

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	start();
	return 0;
}
