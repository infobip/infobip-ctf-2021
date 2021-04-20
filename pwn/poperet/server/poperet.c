#include <stdio.h>

void start() {
	char data[32];
	data[32] = 0x00;
	printf(" Give us your name: ");
	read(0, &data, 112);
	printf("\n");
	printf("HELLO %s\n", data);
	printf("t00t t00t psh psh");
}

int main() {
	system("/bin/true");
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	puts("-------------------------------------");
	puts("-------- free greet service ---------");
	puts("-------------------------------------");
	puts("----------- FEEL GOOD! :) -----------");
	puts("-------------------------------------");
	start();
	puts("");
	puts("---------------------------------------------");
	puts("- thank you very much for using our service -");
	puts("---------------------------------------------");
	return 0;
}
