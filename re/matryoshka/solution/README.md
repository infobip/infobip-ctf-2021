# Solution

We provide a shell script that `uuencode`s a groovy script. Initial groovy script can be dumped by using `uudecode maytryoshka.sh` or just run the shell script without the `rm -rf poly1` and the `poly1` script is dumped:

```groovy
print "Give us your passcode: ";def scan = new Scanner(System.in);def line = scan.nextLine();def bdec = "cHl0aG9uMyAtYyAnaW1wb3J0IHJlO2ltcG9ydCBvcztpbXBvcnQgYmFzZTY0O2ltcG9ydCBzeXM7Qj1iYXNlNjQuYjY0ZGVjb2RlKCJjR1Z5YkNBdFpTQW5kWE5sSUVScFoyVnpkRG82VFVRMUlIRjNLRzFrTlY5b1pYZ3BPM1Z6WlNCTlNVMUZPanBDWVhObE5qUTdiWGtnSkdJOUltTkhhSGRKUXpGNVNVTmphMkZYTkRsSmEwNUVVVEJPUkZFd1RrUlJNRTFwVDNsU2JXSkhSbTVRVjBwb1l6SlZNazVHT1d0YVYwNTJXa2RWYjBsclVqTlhiR1JTVlZaYVRGRXhXbXBWTVVwdllVVTFSbUpIWkZGV1YyZDNWRlpLYjA1RlNrbFNWVFZWVjBkb2QxcHJUbk5UYTJSVldub3dPVWxwYXpkaFYxbG5TMGhPTUdOdGVHeGlhV2RyWVZjMGNGQnFNSHBOVTJ3M1NraEtiR042TUdsSmFuUnRZak5KYjBwSGF6bE5SSE5yWVZSNGVtUklTbk5hVnpSdlNrZGFjMWxYWTNCUGVWSndTM2x6Y0dWNVVubGFXRTExVUZkT2IyTnBhSFpqYlZGdlNrZHNkVmQ1VW5CWVUyeGxZak5LYTB0RFVtMWlSMFp1VjNsU2NGaFRhM0JQTXpGc1dUSm9ka2xEVW5sYVdFMDNabE5qUFNJN2JYa2dKR2c5YldRMVgyaGxlQ2dpUWtKQ1FrSkNRa0pDUWlJcE8yMTVJQ1JrUFUxSlRVVTZPa0poYzJVMk5EbzZaR1ZqYjJSbFgySmhjMlUyTkNna1lpazdiWGtnSkc0OUpHUTlmbk12UTBORFEwTkRRME5EUXk4a2FDOXlPM0J5YVc1MEtHQWtibUFwT3ljPSIpO0lOPSJBQUFBQUFBQUFBIjtQQVRURVJOPSJeKFswLTldezJ9W0EtRl17Mn1beHl6XVswLTldezJ9W0EtRl0pJCI7cGF0dGVybiA9IHJlLmNvbXBpbGUoUEFUVEVSTik7cHJpbnQob3Muc3lzdGVtKEIuZGVjb2RlKCkucmVwbGFjZSgiQkJCQkJCQkJCQiIsSU4pKSkgaWYgcGF0dGVybi5tYXRjaChJTikgZWxzZSBOb25lJw==".decodeBase64();def sdec = new String(bdec).replace("AAAAAAAAAA", line);def proc = ["sh", "-c", sdec].execute();proc.waitFor();print proc.text
```

Script `poly1` now awaits user's input which is unknown on first run, so we need to check what the base64 string is:

```python
python3 -c 'import re;import os;import base64;import sys;B=base64.b64decode("cGVybCAtZSAndXNlIERpZ2VzdDo6TUQ1IHF3KG1kNV9oZXgpO3VzZSBNSU1FOjpCYXNlNjQ7bXkgJGI9ImNHaHdJQzF5SUNja2FXNDlJa05EUTBORFEwTkRRME1pT3lSbWJHRm5QV0poYzJVMk5GOWtaV052WkdVb0lrUjNXbGRSVVZaTFExWmpVMUpvYUU1RmJHZFFWV2d3VFZKb05FSklSVTVVV0dod1prTnNTa2RVWnowOUlpazdhV1lnS0hOMGNteGxiaWdrYVc0cFBqMHpNU2w3SkhKbGN6MGlJanRtYjNJb0pHazlNRHNrYVR4emRISnNaVzRvSkdac1lXY3BPeVJwS3lzcGV5UnlaWE11UFdOb2NpaHZjbVFvSkdsdVd5UnBYU2xlYjNKa0tDUm1iR0ZuV3lScFhTa3BPMzFsWTJodklDUnlaWE03ZlNjPSI7bXkgJGg9bWQ1X2hleCgiQkJCQkJCQkJCQiIpO215ICRkPU1JTUU6OkJhc2U2NDo6ZGVjb2RlX2Jhc2U2NCgkYik7bXkgJG49JGQ9fnMvQ0NDQ0NDQ0NDQy8kaC9yO3ByaW50KGAkbmApOyc=");IN="AAAAAAAAAA";PATTERN="^([0-9]{2}[A-F]{2}[xyz][0-9]{2}[A-F])$";pattern = re.compile(PATTERN);print(os.system(B.decode().replace("BBBBBBBBBB",IN))) if pattern.match(IN) else None'
```

A python script! This script checks for users input against regex. But before we dive more into this, there is more base64:

```perl
perl -e 'use Digest::MD5 qw(md5_hex);use MIME::Base64;my $b="cGhwIC1yICckaW49IkNDQ0NDQ0NDQ0MiOyRmbGFnPWJhc2U2NF9kZWNvZGUoIkR3WldRUVZLQ1ZjU1JoaE5FbGdQVWgwTVJoNEJIRU5UWGhwZkNsSkdUZz09Iik7aWYgKHN0cmxlbigkaW4pPj0zMSl7JHJlcz0iIjtmb3IoJGk9MDskaTxzdHJsZW4oJGZsYWcpOyRpKyspeyRyZXMuPWNocihvcmQoJGluWyRpXSleb3JkKCRmbGFnWyRpXSkpO31lY2hvICRyZXM7fSc=";my $h=md5_hex("BBBBBBBBBB");my $d=MIME::Base64::decode_base64($b);my $n=$d=~s/CCCCCCCCCC/$h/r;print(`$n`);'
```

A perl script! This script calculates MD5 from our supplied input. But there's more base64:

```
php -r '$in="CCCCCCCCCC";$flag=base64_decode("DwZWQQVKCVcSRhhNElgPUh0MRh4BHENTXhpfClJGTg==");if (strlen($in)>=31){$res="";for($i=0;$i<strlen($flag);$i++){$res.=chr(ord($in[$i])^ord($flag[$i]));}echo $res;}'
```

PHP script! This script XOR's our MD5 hashed input with `$flag` which is decoded `DwZWQQVKCVcSRhhNElgPUh0MRh4BHENTXhpfClJGTg==`.

## Unwrapping user input

The key to this polyglot is in the python script regex:
```python
PATTERN="^([0-9]{2}[A-F]{2}[xyz][0-9]{2}[A-F])$"
```

This reveals combinations of user's input that we need to bruteforce to get the flag. So one needs to create a bruteforce script in order to get the flag. If you don't know how to use python itertools or Z3 solver, you can just create a really ugly script and the thing should still work:

```
from base64 import b64decode
from hashlib import md5

NUMS="0123456789"
AFS="ABCDEF"
XYZS="xyz"

flag=b64decode("DwZWQQVKCVcSRhhNElgPUh0MRh4BHENTXhpfClJGTg==")

def check_combo(combo, flag):
    combomd5 = md5(str.encode(combo)).hexdigest()
    solved = ''
    for x in range(len(flag)):
        solved += chr(flag[x]^ord(combomd5[x]))
    if "ibctf" in solved:
        print("{} - {}".format(combo, solved))

for i in NUMS:
    for j in NUMS:
        for k in AFS:
            for l in AFS:
                for m in XYZS:
                    for n in NUMS:
                        for o in NUMS:
                            for p in AFS:
                                check_combo(i+j+k+l+m+n+o+p, flag)
```

Running this weird script will give us the flag:
```
$ python3 solver.py 
09ADx51A - ibctf,mdp$ {#ald%n~.5.&em|9har-
09BDz66B - ibctf06%"+~"<9d|n'&dwj:oh1"x
18DBx99F - ibctf+06  y/#jij(>%,3-we;"n8gqv
27DCx51A - ibctf}j5w%!u+hm`+>rzbzv6i*h=krx
30EDz13D - ibctf)he'"!~+ald+>#6%!0j|o?c'+
46DBy49A - ibctf/<o+"+.*i?`?u{4$tff)<23%(
58BDy81F - ibctf{matryushk4-is-4-p0lygl0t}    <-- here it is
...
```
