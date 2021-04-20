# Solution

The `question` file is a corrupted tar archive that offers the flag in two ways:
- fixing the archive format
- extracting the flag from tar data section

## Extracting the flag from tar data section

We are fairly confident that one can just run binwalk on the `question` file to extract the gzipped stream where the flag is located. The stream can be ungzipped and flag is revealed. This approach was confirmed by CTF participants.

## Fixing the archive format approach

One needs to check the tar format online and recognize that the checksum is not right (offset 148, 8 bytes)

```
00000060: 0000 0000 3030 3030 3030 3000 3030 3031  ....0000644.0001
00000070: 3735 3000 3030 3031 3735 3000 3030 3030  750.0001750.0000
00000080: 3030 3030 3036 3500 3133 3735 3332 3134  0000065.13753214
00000090: 3730 3000 3330 3330 3330 0020 3000 0000  700.303030. 0... <-- 303030 is the checksum
```

The official docs say:
> The chksum field represents a simple sum of all bytes in the header block. When calculating the checksum, the chksum field is treated as if it were all blanks.

Moving to calculating the checksum:
```
>>> with open('../attachments/question', 'rb') as fp:
...     a = fp.read()
... 
>>> b=a[:500]
>>> chk=0
>>> for i in b[:148]+b[156:]:
...     chk+=i
... 
>>> chk
3931
>>> chk+(32*8) # blanks = space = 32 decimal
4187
>>> oct(4187)
'0o10133'
```

Then we change the `question` file checksum:
```
>>> original=a[:148]+b'010133\x00 '+a[156:]
>>> with open('/tmp/original.tar', 'wb') as fp:
...     fp.write(original)
... 
10240
```

And continue unpacking the contents:
```sh
$ cat /tmp/original.tar | tar -x --to-stdout | file -
/dev/stdin: gzip compressed data, was "dot", last modified: Thu Nov 12 11:02:58 2020, from Unix
$ cat /tmp/original.tar | tar -x --to-stdout | gzip -d -
ibctf{l1ttl3_w4rm-m3-up_t4r}
```
