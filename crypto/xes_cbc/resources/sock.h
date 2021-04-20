#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 4444

int sock_prep();
int sock_read(int sock, char* buf, int blen);
int sock_write(int sock, char* buf, int blen);
int sock_accept(int sock, struct sockaddr_in c_addr, int len);
void sock_close(int sock);
