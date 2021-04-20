# Solution

The approach used for this challenge can be the same manual way as in the XES task, you just need to be mindful of block mixing implemented in the CBC mode.

You can start with the flag crib:
```python
$ python3
Python 3.8.5 (default, Jan 27 2021, 15:41:15) 
[GCC 9.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> a='6ee55ebc1e5c3af08162a68d37e4adbc65f50ea9130a04ab9c67a6b359eebef962d848bb4b422db58524ff946c88c8ce'
>>> from binascii import unhexlify
>>> unhexlify(a)
b'n\xe5^\xbc\x1e\\:\xf0\x81b\xa6\x8d7\xe4\xad\xbce\xf5\x0e\xa9\x13\n\x04\xab\x9cg\xa6\xb3Y\xee\xbe\xf9b\xd8H\xbbKB-\xb5\x85$\xff\x94l\x88\xc8\xce'
>>> a=_
>>> crib=b'ibctf{'
>>> iv=a[:16]
>>> a=a[16:]
>>> a
b'e\xf5\x0e\xa9\x13\n\x04\xab\x9cg\xa6\xb3Y\xee\xbe\xf9b\xd8H\xbbKB-\xb5\x85$\xff\x94l\x88\xc8\xce'
>>> iv
b'n\xe5^\xbc\x1e\\:\xf0\x81b\xa6\x8d7\xe4\xad\xbc'
>>> b=[a[i]^crib[i] for i in range(len(crib))]
>>> c=[b[i]^iv[i] for i in range(len(b))]
>>> c
[98, 114, 51, 97, 107, 45]
>>> bytes(c)
b'br3ak-'
```

Since we now have a part of the key, we can decrypt first 6 bytes of each chunk in the long text:
```python
>>> iv = l[:16]
>>> l = l[16:]
>>> chunks = [l[i:i+16] for i in range(0, len(l), 16)]
>>> part2 = [iv[i]^chunks[0][i]^c[i] for i in range(len(c))]
>>> bytes(part2)
b'This i'
>>> part3 = [chunks[0][i]^chunks[1][i]^c[i] for i in range(len(c))]
>>> bytes(part3)
b'ext th'
```

And you end up with:
```
This iXXXXXXXXXXext thXXXXXXXXXXhe flaXXXXXXXXXXchalleXXXXXXXXXXshouldXXXXXXXXXXl to eXXXXXXXXXXypt thXXXXXXXXXXt was XXXXXXXXXX encryXXXXXXXXXXour ReXXXXXXXXXXy XOR XXXXXXXXXX StandXXXXXXXXXX mode.XXXXXXXXXXfor thXXXXXXXXXXge is XXXXXXXXXXld_havXXXXXXXXXX5}. IfXXXXXXXXXXd AES XXXXXXXXXXe, we XXXXXXXXXX this XXXXXXXXXXm I riXXXXXXXXXXe thatXXXXXXXXXXnot suXXXXXXXXXX decryXXXXXXXXXXssage XXXXXXXXXXen thiXXXXXXXXXXould nXXXXXXXXXXlutionXXXXXXXXXXt is rXXXXXXXXXXry andXXXXXXXXXXit. DoXXXXXXXXXXyone eXXXXXXXXXXou, itXXXXXXXXXXse buiXXXXXXXXXX't be XXXXXXXXXXam outXXXXXXXXXXon whaXXXXXXXXXXn thisXXXXXXXXXXake itXXXXXXXXXXer. I XXXXXXXXXXthis iXXXXXXXXXXugh anXXXXXXXXXX statiXXXXXXXXXXon ourXXXXXXXXXXit lonXXXXXXXXXXlreadyXXXXXXXXXXst putXXXXXXXXXXsentenXXXXXXXXXXend toXXXXXXXXXX that XXXXXXXXXX enougXXXXXXXXXXould bXXXXXXXXXXugh. IXXXXXXXXXX, gottXXXXXXXXXXIt is XXXXXXXXXXalreadXXXXXXXXXX
```

You can now get other parts of the key by guessing what the plaintext words might be (`he fla` is most probably `the flag` and `challe` might be `challenge`, etc).

Let's try a guess:
```python
>>> part5 = [chunks[2][i]^chunks[3][i]^c[i] for i in range(len(c))]
>>> bytes(part5)
b'challe'
>>> part5=b'challenge'
>>> rest = [chunks[2][i]^chunks[3][i]^part5[i] for i in range(len(part5))]
>>> bytes(rest)
b'br3ak-M3-'
```

We can now further decrypt our long text and end up with:
```
This is aXXXXXXXext that XXXXXXXhe flag tXXXXXXXchallengeXXXXXXXshould beXXXXXXXl to easiXXXXXXXypt the fXXXXXXXt was preXXXXXXX encrypteXXXXXXXour RevolXXXXXXXy XOR EncXXXXXXX StandardXXXXXXX mode. ThXXXXXXXfor this XXXXXXXge is ibcXXXXXXXld_have_uXXXXXXX5}. If weXXXXXXXd AES in XXXXXXXe, we wouXXXXXXX this proXXXXXXXm I rightXXXXXXXe that yoXXXXXXXnot succeXXXXXXX decrypt XXXXXXXssage becXXXXXXXen this cXXXXXXXould not XXXXXXXlutionaryXXXXXXXt is revoXXXXXXXry and yoXXXXXXXit. Don'tXXXXXXXyone elseXXXXXXXou, it isXXXXXXXse built XXXXXXX't be broXXXXXXXam out ofXXXXXXXon what tXXXXXXXn this teXXXXXXXake it evXXXXXXXer. I hopXXXXXXXthis is lXXXXXXXugh and tXXXXXXX statistiXXXXXXXon our siXXXXXXXit long eXXXXXXXlready? LXXXXXXXst put thXXXXXXXsentence XXXXXXXend to maXXXXXXX that is XXXXXXX enough. XXXXXXXould be lXXXXXXXugh. I thXXXXXXX, gotta gXXXXXXXIt is verXXXXXXXalready.XXXXXXX
```

At this point, just repeat the previous step. You can make a guess and say that `our RevolXXXXXXXy XOR EncXXXXXXX` is most probably `our Revolutionary XOR Encryption`:
```python
>>> part11 = [chunks[8][i]^chunks[9][i]^rest[i] for i in range(len(rest))]
>>> bytes(part11)
b'our Revol'
>>> part11 = b'our Revolutionar'
>>> rest = [chunks[8][i]^chunks[9][i]^part11[i] for i in range(len(part11))]
>>> bytes(rest)
b'br3ak-M3-plZ1br3'
```

And there is the key: `br3ak-M3-plZ1br3`. Let's use it to decrypt the flag:
```python
>>> part16 = [chunks[13][i]^chunks[14][i]^rest[i] for i in range(len(rest))]
>>> bytes(part16)
b'ge is ibctf{sh0u'
>>> part17 = [chunks[14][i]^chunks[15][i]^rest[i] for i in range(len(rest))]
>>> bytes(part17)
b'ld_have_us3ed-43'
>>> part18 = [chunks[15][i]^chunks[16][i]^rest[i] for i in range(len(rest))]
>>> bytes(part18)
b"5}. If we've use"
```

Result: `ge is ibctf{sh0uld_have_us3ed-435}. If we've use`.

Here is decryption and encryption details:
```
- encrypted long text with flag:
05ad2f8804045b3eb9e130c1a2cfd9e733b7759a4f40652df5b130f4fdca8ba034bd32db5005496af8a933c2a8dbd9e73eaa21dc57496379a1b67fecf1d0d8f43fb073d15001402de9e833e2a8dbd9e72eaa2fc557482d7ca1b837ddf5c9cda120f868cb1c00013ce5a422a7a0cedce03bfa2f8a0345292faeb82f9ab1d8c6b22da86b8a1b48146ee6be2aaff5c9d8f86fbf3688021c2929aeaa6682addfc2eb62b877c93b541275efaf7eb1f3d3d1aa79ea1ce702591a28a1ad6b9bb6d8ccf73bcb5be707103669e8fd6eafa7f9fc8779d407e209135b0eade82293fafae9947dc946a316567f4ea0fb26a8a7f4fec978de55ab0e5b5b1feeff2c89e5febc8f76c839a204007373b6fc73b6b0b1fa8f21c724e3264b1e37feab6989a1a6fbd9279556c71e463a6af3984790b0a9e68e20cb45d1104b0036ab844feae9aae2d862cd1ed908463d77e9964fd5b5e6b0aa6d9f64981102172cb0d903c6a4ecade96acd23911b5b7a66f2dc4febfce2b3fa66d064d003035436badf50d7b8ecadb024c632d21a576971b7db54e4faaeb2e635c760d4145a4627f9ca4dcdaeecb4bd32db73c1171e7834b7d351fffafce6f93fdc2cc45c5d5a73bac1588599fbe2a531db6bcc581e7632ee9f149dddedb0ff278931de13415e77ac830db385e0acad378222de1608333dee864182daeda9be3c843f9f394a1029b7d641bd9fafbae32799629b72023169ff864b88c1a1e8a92a9e7dda705b5c33a1d64ebcddabf5ef3b896ed96e1f7d74acc74c82ccaae6b27e8f7dda60125235eedc45b6d3e8dda17d906ed47e4b3f69a58c408887ebdcb2708c7dc27d07067afc930ca2c3fd8ee87cde3acb7f596b3db49b14d886f0dcb67fc76c8a7d00066bef8e16a2dbfdc0e278c771cb5f0d2337b29b5a8c82fec6f16edd2bd914491d24f38458b193f9daad79c870981e0a3437aa9c559f82efc0fb3bc93798014e0a70ee8f4ae5d2ffd7e836d524961f116730aa9b4391c3d4d6fb3dd3379b1b524d23e28540be95de84a933d3619b14063f30839058c3d79c9cef22d5728a0a5f5277c68947b989908bfc33c22f9f041c7c21cb985fc3cc9a9cef34de78de1b5e117f878356b98e8d9cb976d823de0453353f8a9a49c3d38080ed34cf7ed01a19102287be4df091c281b639c821d551563831c6a14fcd80c59dea2edd7a9a1a32557683b84dfc9f87a092608f2e94056b7965c9a701c8c192fc814b893d9c1d66423396ae4dfe9f9ee99248977c98172f762eb3d629aca6f493a9
- encrypted flag:
6ee55ebc1e5c3af08162a68d37e4adbc65f50ea9130a04ab9c67a6b359eebef962d848bb4b422db58524ff946c88c8ce

- key used:
br3ak-M3-plZ1

- decrypted long text with flag:
This is a long text that holds the flag to this challenge. This should be helpful to easily decrypt the flag that was previously encrypted with our Revolutionary XOR Encryption Standard in CBC mode. The flag for this challenge is ibctf{sh0uld_have_us3ed-435}. If we've used AES in CBC mode, we would have this problem. Am I right? I hope that you will not successfully decrypt this message because then this cipher would not be Revolutionary. But it is revolutionary and you know it. Don't let anyone else fool you, it is in-house built and can't be broken. I am out of ideas on what to put in this text to make it even longer. I hope that this is long enough and that the statistics are on our side. Is it long enough already? Let's just put this one sentence at the end to make sure that is is long enough. This should be long enough. I think. OK, gotta go now. It is very long already.
- decrypted flag:
ibctf{sh0uld_have_us3ed-435}
```
