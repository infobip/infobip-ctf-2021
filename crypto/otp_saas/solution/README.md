# Solution

## MTP approach

If you supply the script with a number that is larger than the supplied input, the script will raise an exception and the key will be reused:

```python
while True:
	try:
		s = int(input("How big is the chunk (integer, plz): "))		<-- let's say input 4
		c = input("Your chunk: ")									<-- let's say input "AAA"
		enc(c, k, s)												<-- this guy will raise error ("AAA"[3] is out of bounds)
		print("NEW ROUND! NEXT CHUNK!")
		k = key(len(flag))											<-- key generation is skipped if error is raised
	except KeyboardInterrupt:
		break
	except:
		print("Error!")
		print("Please let's try this all over again!")				<-- let's try this all over again with the same key*
```

The flag is encrypted with an initial key which is not rotated if you immediately raise an error:
```python
k = key(len(flag))
print("Here is how the secret looks after encryption: ", end='')
enc(flag, k, len(flag))
```

This means that we can create as many ciphertexts as we want that are encrypted with the same initial key. Which is not OTP anymore and there are many out-of-the-box tools available on github to break this just by supplying ciphertexts that you have created (see [github MTP](https://github.com/CameronLonsdale/MTP)).

Via socket craft short chunks that are not as big as specified:
```
$ nc 192.168.57.1 9000
This is now the hardened OTP as a service. We encrypt and destroy - 100% security.
Here is how text with a secret flag looks after encryption: 7e075508663e406a1b5b0a45131f630d3d6f2a582d5a2d0c13432e51391843014c227239382c100e4b1c
OK, now let's take your data in chunks and do you a service!
NOTE: no chunks bigger than 42
How big is the chunk (integer, plz): 42
Your chunk: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
792a752e0716720b33782870342513380f03052918362319022f0676273231392011000d0a08352b77Error!
Please let's try this all over again!
How big is the chunk (integer, plz): 42
Your chunk: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
792a752e0716720b33782870342513380f03052918362319022f0676273231392011000d0a08352b77Error!
Please let's try this all over again!
How big is the chunk (integer, plz): 42
Your chunk: BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
7a29762d04157108307b2b733726103b0c00062a1b35201a012c05752431323a2312030e090b362874Error!
Please let's try this all over again!
How big is the chunk (integer, plz): 42
Your chunk: CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
7b28772c05147009317a2a723627113a0d01072b1a34211b002d04742530333b2213020f080a372975Error!
Please let's try this all over again!
How big is the chunk (integer, plz): 42
Your chunk: DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
7c2f702b0213770e367d2d753120163d0a06002c1d33261c072a03732237343c251405080f0d302e72Error!
Please let's try this all over again!
How big is the chunk (integer, plz): 42
Your chunk: EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
7d2e712a0312760f377c2c743021173c0b07012d1c32271d062b02722336353d241504090e0c312f73Error!
Please let's try this all over again!
How big is the chunk (integer, plz): ^C
```

The given hex strings can be imported into `mtp` and used for decryption of the flag:

```
{"decryptions": ["Flag is ibctf{1ts-n0t-OTP-if_k3y-r3usedd}", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB", "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC", "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD", "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"], "key": "386b346f4657334a72396931756452794e42446859776258436e4737667370786150414c4b49746a36"}
```

## One time A's approach

There is no need to overthink things with MTP, but it is still valid. You can just send `"A"*42`, xor result with `"A"*42` which will give you the key and then use that key to decrypt the initial message.

