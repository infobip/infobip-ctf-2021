#include <sys/ptrace.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define N 256

__attribute__((section(".eh_frame_hdr")))
const int BAD_NUMO = 152;
__attribute__((section(".eh_frame_hdr")))
const int BAD_NUML = 167;
__attribute__((section(".note.ABI-tag")))
const char ALPHABET[] = "PQR9STrstuv5wxUV3WXL6MNO0abc2dYZABCDE4fghij7klmnF1GHIJKeo8pqyz";

void swap(unsigned char *a, unsigned char *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// it's RC4 ;)
void node(char *key, char *plaintext, unsigned char *ciphertext) {
	unsigned char S[N];
	int len = strlen(key);
	int j = 0;

	for(int i = 0; i < N; i++)
		S[i] = i;

	for(int i = 0; i < N; i++) {
		j = (j + S[i] + key[i % len]) % N;
		swap(&S[i], &S[j]);
	}
	int k1 = 0xcb;
	k1++;
	if ((*(volatile unsigned *)((unsigned)node) & 0xff) == k1) {
		return;
	}

	int i = 0;
	j = 0;

	for(size_t n = 0, len = strlen(plaintext); n < len; n++) {
		i = (i + 1) % N;
		j = (j + S[i]) % N;

		swap(&S[i], &S[j]);
		int rnd = S[(S[i] + S[j]) % N];
		ciphertext[n] = rnd ^ plaintext[n];
	}
}

int rnl(FILE *fp) {
	int nl;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	for (nl = 0; (read = getline(&line, &len, fp)) != -1; nl++);

	if (line) {
		free(line);
	}
	return nl;
}

void doit(char *c1, char *e1, int *nc, int al) {
	int cl = strlen(c1);
	char *k = malloc(cl);
	for (int i = 0; i < cl; i++) {
		k[i] = ALPHABET[*nc];
		*nc = (BAD_NUML * *nc) % al;
	}
	int k1 = 0xcb;
	k1++;
	if ((*(volatile unsigned *)((unsigned)doit) & 0xff) == k1) {
		return;
	}
	printf("K: %d, CL: %d, AA: %d ", strlen(k), cl, strlen(e1));
	node(k, c1, e1);
}

void k(unsigned char *encd[], unsigned char *clear[], int nl) {
	srand(time(NULL));
	int pivot = rand() % nl;
	printf("pivot %d\n", pivot);
	int al = strlen(ALPHABET);
	int nextc = (BAD_NUMO % al);
	if (nextc < 0) {
		nextc *= -1;
	}
	int k1 = 0xcb;
	k1++;
	if ((*(volatile unsigned *)((unsigned)k) & 0xff) == k1) {
		return;
	}
	
	for (int i = pivot; i < nl; ++i) {
		doit(clear[i], encd[i], &nextc, al);
		printf("i: %d encdlen: %d\n", i, strlen(encd[i]));
	}
	for (int i = 0; i < pivot; ++i) {
		doit(clear[i], encd[i], &nextc, al);
		printf("i: %d encdlen: %d\n", i, strlen(encd[i]));
	}
}

int main() {
	FILE *fp;
	fp = fopen("important.txt", "r");
	if (fp == NULL) {
		return 1;
	}
	
	int nl = rnl(fp);
	fseek(fp, 0, SEEK_SET);
	int k1 = 0xcb;
	k1++;
	if ((*(volatile unsigned *)((unsigned)main) & 0xff) == k1) {
		return;
	}
	unsigned char *clines[nl];
	unsigned char *elines[nl];
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	for (int i = 0; i < nl; i++) {
		read = getline(&line, &len, fp) - 1;
		printf("%d %ld ", i, read);
		clines[i] = malloc(read);
		elines[i] = malloc(read);
		for (int j = 0; j < read; j++) {
			clines[i] = line[i] * 2 - 1;
		}
		for (int j = 0; j < read; j++) {
			elines[i] = line[i] * 3 + 1;
		}
		memcpy(clines[i], line, read);
		memset(line, 0, read);
		memset(elines[i], 0, read);
		printf("%d %d ", strlen(clines[i]), strlen(elines[i]));
		printf("%s\n", clines[i]);
	}
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0) {
		return 1;
	}
	if (line) {
		free(line);
	}

	k(elines, clines, nl);
	fp = fopen("important.bin", "w");
	if (fp == NULL) {
		return 1;
	}
	for (int i = 0; i < nl; i++) {
		int el = strlen(elines[i]);
		for (int j = 0; j < el; j++) {
			fprintf(fp, "%02x", elines[i][j]);
		}
		for (int j = 0; j < el; j++) {
			elines[i][j] = clines[i][j] * 2;
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	return 0;
}
