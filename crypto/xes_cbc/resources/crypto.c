#include <string.h>

#include "crypto.h"

void xor(char* src, char* key, char* dst, int srclen, int keylen) {
	for (int i = 0; i < srclen; i++) {
		dst[i] = src[i] ^ key[i % keylen];
	}
}

int xes_size(int slen) {
    return slen % __XES_BLOCK_SIZE
         ? ((int) (slen / __XES_BLOCK_SIZE) + 1) * __XES_BLOCK_SIZE
         : slen + __XES_BLOCK_SIZE;
}

int xes_pad(char* t, u_int tlen) {
	int esize = xes_size(tlen);
	int padlen = esize - tlen;
	memset(t + tlen, padlen, padlen);
	return padlen;
}

int xes_unpad(char* t, u_int tlen) {
	int padlen = t[tlen - 1];
	t[tlen - padlen] = '\0';
	return padlen;
}

void xes_encrypt(char* text, char* key, u_int tlen, u_int klen, char* iv, char* dst) {
	int plen = xes_pad(text, tlen);
	memcpy(dst, iv, __XES_BLOCK_SIZE);

	char tmp[__XES_BLOCK_SIZE], *dptr = dst + __XES_BLOCK_SIZE, *tptr = text;
	xor(tptr, iv, tmp, __XES_BLOCK_SIZE, __XES_BLOCK_SIZE);
	xor(tmp, key, dptr, __XES_BLOCK_SIZE, klen);
	tptr += __XES_BLOCK_SIZE;

	while (tptr < text + tlen + plen) {
		xor(tptr, dptr, tmp, __XES_BLOCK_SIZE, __XES_BLOCK_SIZE);
		dptr += __XES_BLOCK_SIZE;
		xor(tmp, key, dptr, __XES_BLOCK_SIZE, klen);
		tptr += __XES_BLOCK_SIZE;
	}
}

void xes_decrypt(char* crypt, char* key, u_int clen, u_int klen, char* dst) {
	char iv[__XES_BLOCK_SIZE], tmp[__XES_BLOCK_SIZE], 
		 *cptr = crypt + clen - __XES_BLOCK_SIZE,
		 *dptr = dst + (clen - 2*__XES_BLOCK_SIZE); // last block start at end - len(IV) - 16B
	
	while (cptr >= crypt + __XES_BLOCK_SIZE) {
		xor(cptr, key, tmp, __XES_BLOCK_SIZE, klen);
		cptr -= __XES_BLOCK_SIZE;
		xor(cptr, tmp, dptr, __XES_BLOCK_SIZE, __XES_BLOCK_SIZE);
		dptr -= __XES_BLOCK_SIZE;
	}
	
	xor(cptr, key, tmp, __XES_BLOCK_SIZE, klen);
	cptr -= __XES_BLOCK_SIZE;
	memcpy(iv, cptr, __XES_BLOCK_SIZE);
	xor(tmp, iv, dptr, __XES_BLOCK_SIZE, __XES_BLOCK_SIZE);
	
	xes_unpad(dst, clen - __XES_BLOCK_SIZE);
}
