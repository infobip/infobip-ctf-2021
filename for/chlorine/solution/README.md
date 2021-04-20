# Solution

The wireshark dump contains an iodine DNS tunnel. Luckily, there is a very nice writeup on how to decrypt iodine DNS tunnels and our small challenge even does not use any passwords - which makes it a simple base128 decode.

The writeup which needs to be replicated was made by stalkr: https://blog.stalkr.net/2010/10/hacklu-ctf-challenge-9-bottle-writeup.html.

You can download all the needed files from https://stalkr.net/files/hack.lu/2010/9/ and you will need only four items:
- `encoder.c`
- `extract_dns.py`
- `iodine-0.6.0-rc1.tar.gz`
- `uncompress.c`

We further proceed by extracting `iodine-0.6.0-rc1.tar.gz` and moving `encoder.c`, `uncompress.c` and `extract_dns.py` to the `iodine-0.6.0-rc1/src` folder.

From there we compile both `.c` files:
```sh
gcc -Wall -o encoder encoder.c base128.c base32.c base64.c
gcc -Wall -o uncompress uncompress.c -lz
```

To successfully run `extract_dns.py` you need to have both `python2.7` and `python2-scapy` setup on your PC. Additionally, the script might not like the `chlorine.pcap` as the input file, so make sure to convert it first:
```sh
gunzip chlorine.gz > chlorine.pcap
tshark -r chlorine.pcap -w newchlorine.pcap -F libpcap
```

Before running the `extract_dns.py` script, make sure to change the `topdomain` variable to `.ibctf.local.` and `input` variable to `newchlorine.pcap`.

```sh
$ python extract_dns.py 
WARNING: No route found for IPv6 destination :: (no default route?)
Successfully extracted 23 packets into ./extracted.cap
```

After opening `extracted.cap` you will find two HTTP requests and the second one (packet no. 20) will have the flag:

```
0000   45 00 00 55 a2 88 40 00 40 06 82 18 0a 00 01 01   E..U..@.@.......
0010   0a 00 01 02 1f 40 e3 90 73 b2 b6 9c 66 c5 b1 b2   .....@..s...f...
0020   80 19 01 f9 ef de 00 00 01 01 08 0a f7 59 d4 10   .............Y..
0030   5b cf f0 f2 69 62 63 74 66 7b 6e 30 74 2d 63 68   [...ibctf{n0t-ch
0040   6c 30 72 31 6e 33 33 5f 62 75 74 5f 31 30 64 31   l0r1n33_but_10d1
0050   6e 33 33 7d 0a                                    n33}.
```
