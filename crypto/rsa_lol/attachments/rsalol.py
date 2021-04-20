#!/usr/bin/sage
from sage.all import *
from binascii import hexlify
from sys import argv

if len(argv) != 3:
    print("Please specify a number")
    sys.exit(1)

_, p, q = argv
if not p.isdigit() or not q.isdigit():
    print("Please specify number as argument")
    sys.exit(1)

p = Integer(p)
q = Integer(q)
n = p * q 
phi = p * (q - 1)

e = 65537
d = xgcd(e, phi)[1] % phi
assert mod(d * e, phi) == 1

flag = raw_input("Specify your secret: ")
m = int(hexlify(flag), 16)
assert m < n
c = power_mod(m, e, n)
assert power_mod(c, d, n) == m

with open("pub.txt", "w") as fp:
    fp.write("(n, e) = (%d, %d)\n" % (n, e))
    fp.write("c = %d" % c)

