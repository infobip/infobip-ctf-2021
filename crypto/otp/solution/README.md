# Solution

The script has comments on when the script was edited: `2020-10-07 16:48`.

The script uses time to seed random and generate a random sample:
```python
t = int(time.time())
random.seed(t)
key = ''.join(random.sample(string.ascii_letters + string.digits, len(flag)))
ciphertext = ''.join([format(ord(key[i])^ord(flag[i]), '02x') for i in range(len(flag))])
```

If random uses time to seed random, we can replicate the same random state by bruteforce and xor ciphertext with recreated key(s).

The function `time.time()` returns UNIX seconds, so we convert our timestamp to UNIX seconds:
```python
>>> ts="2020-10-07 16:48"
>>> time.mktime(datetime.datetime.strptime(ts, "%Y-%m-%d %H:%M").timetuple())
1602082080.0
```

So let's just try and check the next 1000 seconds after the specified edit time:
```python
>>> edit=1602082080 
>>> flag
'2b511a420c1c3a601c33421b0554387539594824076905'
>>> flag=unhexlify(flag)
>>> for i in range(edit, edit+1000):                 
...     random.seed(i)                               
...     key = ''.join(random.sample(string.ascii_letters + string.digits, len(flag)))
...     ciphertext = ''.join([chr(ord(key[i])^flag[i]) for i in range(len(flag))])
...     if "ibctf" in ciphertext:                    
...             print(ciphertext, key)               
... 
ibctf{n0-r4nd0m-n0-OTP} B3y6jgTP1AvuadUXWiekS9x
```
