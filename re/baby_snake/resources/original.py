# ibctf{snake-snake_s3v3rus_snake}

a = input('a:')		 # v}|kydlq~tz2lq~tz@l,i,mjl@lq~tzb
b = int(input('b:')) # 31
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

