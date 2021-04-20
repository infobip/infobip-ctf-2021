.PHONY: local remote

FLAG=ibctf{cl4ss1c_buffer-0verfl0w}
BIN=greet
CFLAGS=-O0 -fno-stack-protector -no-pie -z execstack
CC=gcc

local:
	$(CC) -o $(BIN) $(CFLAGS) $(BIN).c

