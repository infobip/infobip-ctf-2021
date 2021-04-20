.PHONY: local remote

BIN=golf
CFLAGS=-O0 -fno-stack-protector -no-pie -z execstack
CC=gcc

local:
	$(CC) -o $(BIN) $(CFLAGS) $(BIN).c -lseccomp

