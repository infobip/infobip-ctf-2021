# Solution

The Translator is a simple reversing challenge. One should analyze the x86-64 assembly and deduce the following flow:
- there is encrypted flag: `\x1eRSD9\x12\x07_P\x07\t3>\x15l4V\x03\x33\x1fX\x0eo\x13\x05W^\x13`
- there is encoded key stored: `1mmmdbx9tbxdd7dn3ldaugd74tm4`
- there is an alphabet used for encoding: `faibec_d1e]flg}hgihjzkyl0mkn9oxpvq2r6sdtuuowpvsx7y4zt0w15233n4b586a7[8-9q{r}{[j]c-m_`

The key encoding algorithm is simple:
- search for the character starting from position 1 and step by +2 until character found
- when character is found, the character 1 position before (adjacent to) the character found is the character which we have use and replace with the character found

for instance:
- `1mmm` is encoded key
- search for `1` in the alphabet: `...4zt0w1523...`
- the character one position before `1` is `w` so this is the decoded value
- further search for `m` in the alphabet: `...yl0mkn...`
- the character one position before `m` is `0` so this is the decoded value
- result is `w000`

So if we decode the key completely we will get: `w000_is-dis__a_k3y_ful_and0n`.

After we have the key, it is only important to understand how to decrypt the flag, which is basically a simple XOR:

```
>>> key=b"w000_is-dis__a_k3y_ful_and0n"
>>> flag=b"\x1eRSD9\x12\x07_P\x07\t3>\x15l4V\x03\x33\x1fX\x0eo\x13\x05W^\x13"
>>> ''.join(chr(flag[i]^key[i]) for i in range(len(flag)))
'ibctf{tr4nzlat3_ezly-b0rk3n}'
```
