#include <stdio.h>

void greet() {
    char data[256];
    printf(" Preparing a place to store your name on our infrastructure: %p :) hehe\n", data);
    memset(data, 0, 256);
    printf(" Give us your name: ");
    read(0, &data, 512);
    printf("HELLO %s", data);
}

int main() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    puts("-------------------------------------");
    puts("-------- free greet service ---------");
    puts("-------------------------------------");
    puts("----------- FEEL GOOD! :) -----------");
    puts("-------------------------------------");
    greet();
    puts("---------------------------------------------");
    puts("- thank you very much for using our service -");
    puts("---------------------------------------------");
    return 0;
}
