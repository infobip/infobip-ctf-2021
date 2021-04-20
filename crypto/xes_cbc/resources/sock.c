#include <string.h>

#include "sock.h"

int sock_prep() {
	struct sockaddr_in s_addr;
	int sfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sfd < 0) {
		return -1;
	}

	memset((char*) &s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = INADDR_ANY;
	s_addr.sin_port = htons(PORT);

	if (bind(sfd, (struct sockaddr*) &s_addr, sizeof(s_addr)) < 0) {
		return -1;
	}	

	listen(sfd, 5);
	return sfd;
}

int sock_read(int sock, char* buf, int blen) {
	return recv(sock, (void*) buf, blen, 0);
}

int sock_write(int sock, char* buf, int blen) {
	return send(sock, (void*) buf, blen, 0);
}

int sock_accept(int sock, struct sockaddr_in c_addr, int len) {
	return accept(sock, (struct sockaddr*) &c_addr, &len);
}

void sock_close(int sock) {
	close(sock);
}
