# Solution

Reverse the `baby_snake.py` by base64 decoding the payload.

Obfuscation will need some time to reveal what the code does, but in the end it is a scripting language - some of the code can be executed and functions can be replaced easily with a text editor (Find and replace feature).

The end result should look something like this:

```python
a = input('a:')
b = int(input('b:'))
print(str().join([chr(ord(a[i]) ^ b) for i in range(32)]))

if b<<2!=124:
	raise
if a[17:26] != "@l,i,mjl@":
	raise
pos = [6, 11, 12, 17, 26, 31]
for i in range(0, len(pos), 2):
	if a[pos[i]:pos[i+1]] != "lq~tz":
		raise
if a[11] != '2':
	raise
```

The most relevant part of the script are the checks performed in the end.

```python
if b<<2!=124:
	raise
```

Snippet reveals that `b` should be `31`:
```
>>> 124>>2
31
```

The following snippet:
```python
if a[17:26] != "@l,i,mjl@":
	raise
pos = [6, 11, 12, 17, 26, 31]
for i in range(0, len(pos), 2):
	if a[pos[i]:pos[i+1]] != "lq~tz":
		raise
if a[11] != '2':
	raise
```

Reveals that `a` from 17 to 26 is `@l,i,mjl@` and `lq~tz` is specified in the following ranges:
- 6 til 11
- 12 til 17
- 26 til 31

Also, the `a[11] != '2'` means that the 11th character is 2.

This results in `a` being:
```
xxxxxxlq~tz2lq~tz@l,i,mjl@lq~tz
```

The line `print(str().join([chr(ord(a[i]) ^ b) for i in range(32)]))` reveals that the maximum length of `a` is `32` and our known `a` is of length 31, meaning that the end result of what we know so far is (`x` means that the character is unknown):
```
xxxxxxlq~tz2lq~tz@l,i,mjl@lq~tzx
```

If we XOR what we know with 31, we get:
```
>>> a = 'xxxxxxlq~tz2lq~tz@l,i,mjl@lq~tzx'
>>> b = 31
>>> print(str().join([chr(ord(a[i]) ^ b) for i in range(32)]))
ggggggsnake-snake_s3v3rus_snakeg
```

The start and end of the string is not revealed in the script itself, but you already know the flag format (`ibctf{...}`) and by observation:

```
ggggggsnake-snake_s3v3rus_snakeg
ibctf{.........................}
```

Meaning that the flag can only be:
```
ibctf{snake-snake_s3v3rus_snake}
```
