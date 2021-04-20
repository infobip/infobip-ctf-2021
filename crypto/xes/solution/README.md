# Solution

The no bruteforce way:

We only have encrypted text provided without a key. Since we know the format of the flag `ibctf{...}` we can issue a known plaintext attack on the ciphertext by XOR-ing the first 6 bytes with `ibctf{`:

```
>>> from binascii import unhexlify
>>> ct = unhexlify('035615404b0b0a450540020f1901555f1d0c04455d0c1340456b55400b09')
>>> ct
b'\x03V\x15@K\x0b\nE\x05@\x02\x0f\x19\x01U_\x1d\x0c\x04E]\x0c\x13@EkU@\x0b\t'
>>> crib = b"ibctf{"
>>> ''.join([chr(ct[i]^crib[i]) for i in range(6)])
'j4v4-p'
```

What we can do know is try all possible combinations of `j4v4-p` after the first 6 bytes in order to see if key is rotated:

```
>>> for i in range(6, len(ct)):
...     try:
...             print(i, end=' ')
...             for j in range(6):
...                     print(chr(ct[j+i]^k[j]), end='')
...             print()
...     except:
...             print()
... 
6 `qst/
7 /166"i
8 ott;4q
9 *6y-,%
10 h;o5x/
11 e-warm  <--- this guy looks the most promising
12 s5#k0|
13 ka))!t
14 ?kk8)5
15 5)z0h-
16 w8rqp|
17 f03i!c
18 nq+8>0
19 /iz'm5
20 78eth
1 f'6qF%
22 yt3_x0  <--- if key is of size 11, this is the next chunk
23 *qam{
24 /_#t&y
25 a6?$
26 ?t}=
27 *?
28 a=
29 c
```

If the key is repeated on index 11, this means that the key is of size 11 and the next plaintext would be at index 22:

```
ibctf{.....e-warm.....yt3_x0..
j4v4-p.....j4v4-p.....j4v4-p..
```

The last char is most certainly `}`, so we can leak another char from the key.

```
>>> chr(ct[-1]^ord('}'))
't'
```

```
ibctf{.1...e-warm.p...yt3_x0.}
j4v4-p.t...j4v4-p.t...j4v4-p.t
```

The key is basically guessable when you decrypt it with a crib, but at this point you can certainly observe possible chars between `p` and `t` (the plaintext `warm.p` is most probably `warmup` and `x0.` might by `x0r` and little trial and error will show that this is true):

```
ibctf{s1...e-warmup...yt3_x0r}
j4v4-pyt...j4v4-pyt...j4v4-pyt
```

Aaaand, now its obvious that its `python`:

```
ibctf{s1m/le-warmup-2byt3_x0r}
j4v4-pythonj4v4-pythonj4v4-pyt
```

Well... the flag seems odd still, but this is bruteforceable easily (or just observe that `s1m/le` might be `s1mple`, and `o` should be `0`):

```
ibctf{s1mple-warmup-mbyt3_x0r}
j4v4-pyth0nj4v4-pyth0nj4v4-pyt
```
