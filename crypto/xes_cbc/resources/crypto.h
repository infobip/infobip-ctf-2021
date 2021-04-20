#include <sys/types.h>

#define __XES_BLOCK_SIZE 16

void xor(char* src, char* key, char* dst, int srclen, int keylen);
int xes_size(int slen);
int xes_pad(char* t, u_int tlen);
int xes_unpad(char* t, u_int tlen);
void xes_encrypt(char* text, char* key, u_int tlen, u_int klen, char* iv, char* dst);
void xes_decrypt(char* crypt, char* key, u_int clen, u_int klen, char* dst);
