# Solution

The binary has a function `am` that contains instructions to initiate custom syscalls. We can issue a `sigreturn` syscall which loads registers from the stack, so we build a frame to load our custom register values and issue another `execve` syscall to leverage a shell.

The mechanism used in this challenge is called SROP.

Solution is in `sig-solution.py`.

```sh
$ python3 sig-solution.py 
[+] Opening connection to localhost on port 9000: Done
[*] Switching to interactive mode
$ id
uid=1000(ctf) gid=1000(ctf) groups=1000(ctf)
$ cat flag.txt
ibctf{n0t_int-but-r0p-1247321}
```
