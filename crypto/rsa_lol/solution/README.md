# Solution to rsalol challenge

The Euler totient function used reveals that the used primes are the same. Meaning that you can calculate `p` and `q` as `sqrt(n)`.

After you've got your one prime, you can just decrypt the message:

```python
# c, n and e are known
p = q = sqrt(n)
phi = p * (q - 1)
d = inverse_mod(e, phi)
m = power_mod(c, d, n)

print(unhexlify(hex(m)))
> "why can't you just pick one prime for rsa??? works perfectly without the second one haha ibctf{th1s_1s_n0t-RSA-lol}"
```
