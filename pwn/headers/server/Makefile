.PHONY: local remote

BIN=headers
CFLAGS=-O0 -fno-stack-protector -no-pie -nodefaultlibs -L./libc-2.23.so
CC=gcc

local:
	$(CC) -o $(BIN) $(CFLAGS) $(BIN).c -lgcc -lc

