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
