#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <arpa/inet.h>

#include "crypto.h"
#include "sock.h"

#define INPUT_SIZE 2048

void xes_online(int sock) {
	char* title = "- Revolutionary XOR Encryption Standard in CBC mode -\n";
	char* input = (char*) malloc(INPUT_SIZE);
	char* key = (char*) malloc(__XES_BLOCK_SIZE);
	char *out, *unhex, mode;
	int i, olen, ilen, klen;

	sock_write(sock, title, strlen(title));

	strncpy(input, "Your input: ", 12);
	sock_write(sock, input, INPUT_SIZE);
	memset(input, 0, INPUT_SIZE);
	sock_read(sock, input, INPUT_SIZE);
	ilen = strlen(input) - 1;

	strncpy(key, "Your key: ", 10);
	sock_write(sock, key, __XES_BLOCK_SIZE);
	memset(key, 0, __XES_BLOCK_SIZE);
	sock_read(sock, key, __XES_BLOCK_SIZE);
	klen = strlen(key) - 1;

	sock_write(sock, " (d)ecrypt or (e)ncrypt? ", 25);
	sock_read(sock, &mode, 1);
	
#define _HEX_SIZE 2 
	switch(mode) {
		case 'd':
		case 'D':
			// TODO check hex string (len, 2, bla)
			olen = (int) (ilen / _HEX_SIZE);
			unhex = (char*) malloc(olen);
			
			for (unsigned int uch, i = 0; i < ilen; i += _HEX_SIZE) {
				sscanf(input + i, "%02x", &uch);
				unhex[i / _HEX_SIZE] = (char) uch;
			}
			
			out = (char*) malloc(olen - __XES_BLOCK_SIZE);
			sock_write(sock, "Pushing data into decryption ...\n", 33);
			xes_decrypt(unhex, key, olen, klen, out);					
			sock_write(sock, "Decrypt result: ", 16);
			sock_write(sock, out, strlen(out));
			break;

		case 'e':
		case 'E':
			olen = xes_size(ilen) + __XES_BLOCK_SIZE;
			out = (char*) malloc(olen);
			char hex[_HEX_SIZE + 1], iv[__XES_BLOCK_SIZE];
			
			sock_write(sock, "Generating IV\n", 14);
			getrandom(iv, __XES_BLOCK_SIZE, 0);
			sock_write(sock, "Pushing data into encryption ...\n", 33);
			xes_encrypt(input, key, ilen, klen, iv, out);	
					
			sock_write(sock, "Encrypt result: ", 16);
			unhex = (char*) malloc(olen * 2);
			memset(unhex, 0, olen * 2);
			for (i = 0; i < olen; i++) {
				snprintf(hex, _HEX_SIZE + 1, "%02x", (unsigned int)(unsigned char) *(out + i));
				memcpy(unhex + (i * 2), hex, 2);
			}
			sock_write(sock, unhex, strlen(unhex));
			break;

		default:
			sock_write(sock, "Invalid mode! (d/e)\n", 20);

	}	
}

int main () {
	struct sockaddr_in c_addr;
	char* sockbuf;
	int sock, pid, clen, csock;

	sock = sock_prep();
	clen = sizeof(c_addr);

	while (1) {
		csock = sock_accept(sock, c_addr, clen);
		printf("[!] Received connection from client %s\n", inet_ntoa(c_addr.sin_addr));
		
		if (csock < 0) {
			perror("Func accept ERR");
			return 1;
		}

		pid = fork();
		
		if (pid < 0) {
			perror("Func fork ERR");
			return 1;
		}

		if (pid == 0) {
			xes_online(csock);
			sock_close(csock);
			return 0;
		}
	}

	sock_close(sock);
	return 0;
}
