#include <stdio.h>
#include <string.h>

unsigned char* t = "faibec_d1e]flg}hgihjzkyl0mkn9oxpvq2r6sdtuuowpvsx7y4zt0w15233n4b586a7[8-9q{r}{[j]c-m_";
unsigned char* y = "1mmmdbx9tbxdd7dn3ldaugd74tm4";
unsigned char* a = "\x1eRSD9\x12\x07_P\x07\t3>\x15l4V\x03\x33\x1fX\x0eo\x13\x05W^\x13";

int drv(char *in, char *t, char *y, char *a) {
	if (strlen(in) != 28) {
		return 0;
	}
	for (int i = 0; i < 28; ++i) {
		for (int j = 1; j < strlen(t); j+=2) {
			if (t[j] == y[i]) {
				if ((in[i] ^ t[j-1]) != a[i]) {
					return 0;
				}
				break;
			}
		}
	}
	return 1;
}

int main() {
	// ibctf{tr4nzlat3_ezly-b0rk3n}
	// w000_is-dis__a_k3y_ful_and0n
	// 1mmmdbx9tbxdd7dn3ldaugd74tm4
	char f[32];
	fgets(f, sizeof(f), stdin);
	f[strlen(f)-1] = '\0';
	if (drv(f, t, y, a)) {
		printf("gz\n");
		return 0;
	}
	printf("nope\n");
	return 1;
}
