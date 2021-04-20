import random
import string

def key(l):
	return ''.join(random.sample(string.ascii_letters + string.digits, l))

def enc(p, k, l):
	for i in range(len(k)):
		print(format(ord(p[i])^ord(k[i]), "02x"), end='')
	print()

print("This is now the hardened OTP as a service. We encrypt and destroy - 100% security.")
flag = "Flag is ibctf{1ts-n0t-OTP-if_k3y-r3usedd}."
k = key(len(flag))
print("Here is how text with a secret flag looks after encryption: ", end='')
enc(flag, k, len(flag))
print("OK, now let's take your data in chunks and do you a service!")
print("NOTE: no chunks bigger than {}".format(len(flag)))
while True:
	try:
		s = int(input("How big is the chunk (integer, plz): "))
		c = input("Your chunk: ")
		enc(c, k, s)
		print("NEW ROUND! NEXT CHUNK!")
		k = key(len(flag))
	except KeyboardInterrupt:
		break
	except:
		print("Error!")
		print("Please let's try this all over again!")
	
