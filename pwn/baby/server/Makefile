.PHONY: local remote

FLAG=ibctf{simpl3st_of-th3m-477}
BIN=baby
CFLAGS=-O0
CC=gcc

local:
	$(CC) -o $(BIN) $(CFLAGS) $(BIN).c

remote:
	sed "s/ibctf{...}/$(FLAG)/" $(BIN).c | $(CC) -o $(BIN) $(CFLAGS) -xc -
