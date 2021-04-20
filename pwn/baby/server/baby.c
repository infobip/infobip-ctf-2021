#include <stdio.h>

void a() {
    puts("ibctf{...}");
}

int main() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    puts("-------------------------------------");
    puts("-------- free greet service ---------");
    puts("-------------------------------------");
    puts("----------- FEEL GOOD! :) -----------");
    puts("-------------------------------------");
    char data[32];
    char admin[80];
    admin[9] = 0x00;
    data[32] = 0x00;
    printf(" Give us your name: ");
    read(0, &data, 112);
    printf("\n");
    printf("HELLO %s", data);
    if (strncmp(admin, "TUNIVERSE", 8) == 0) {
    	a();
    }
    puts("---------------------------------------------");
    puts("- thank you very much for using our service -");
    puts("---------------------------------------------");
    return 0;
}
