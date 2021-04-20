# script: otp.py
# date: 2020-10-07
# user: john
# last change: 16:48
# description: ultra secure otp script
import time
import random
import argparse
import string

parser = argparse.ArgumentParser(description='the most secure encryption program')
parser.add_argument('flag', type=str, help='your biggest secret')
flag = parser.parse_args().flag

print(len(flag))
t = int(time.time())
random.seed(t)
key = ''.join(random.sample(string.ascii_letters + string.digits, len(flag)))
ciphertext = ''.join([format(ord(key[i])^ord(flag[i]), '02x') for i in range(len(flag))])
print(ciphertext)
