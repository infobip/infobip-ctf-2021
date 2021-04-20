# Solution

The gzip file is a packet capture file. Opening the dump in wireshark and filtering with `ip.addr == 192.168.56.1`, will reveal weird TCP traffic.

Choose `Follow TCP stream` and observe that this is a transfer of a keylogger log file. Packet no. 341 is the one that has the flag:

```
+i
-i					<-- i
+b
-b					<-- ib
+c
-c					<-- ibc
+t
-t					<-- ibct
+f
-f					<-- ibctf
+Shift_L
+bracketleft
-bracketleft		<-- ibctf{
-Shift_L
+x
-x					<-- ibctf{x
+k
-k					<-- ibctf{xk
+3
-3					<-- ibctf{xk3
+y
-y					<-- ibctf{xk3y
+l
-l					<-- ibctf{xk3yl
+0
-0					<-- ibctf{xk3yl0
+g
-g					<-- ibctf{xk3yl0g
+g
-g					<-- ibctf{xk3yl0gg
+3
-3					<-- ibctf{xk3yl0gg3
+r
-r					<-- ibctf{xk3ylogg3r
+minus
-minus				<-- ibctf{xk3yl0gg3r-
+i
-i					<-- ibctf{xk3yl0gg3r-i
+s
-s					<-- ibctf{xk3yl0gg3r-is
+BackSpace
-BackSpace			<-- ibctf{xk3yl0gg3r-i
+z
-z					<-- ibctf{xk3yl0gg3r-iz
+minus
-minus				<-- ibctf{xk3yl0gg3r-iz-
+Shift_L
-Shift_L
+l
-l					<-- ibctf{xk3yl0gg3r-iz-l
+i
-i					<-- ibctf{xk3yl0gg3r-iz-li
+n
-n					<-- ibctf{xk3yl0gg3r-iz-lin
+BackSpace
-BackSpace			<-- ibctf{xk3yl0gg3r-iz-li
+BackSpace
-BackSpace			<-- ibctf{xk3yl0gg3r-iz-l
+BackSpace
-BackSpace			<-- ibctf{xk3yl0gg3r-iz-
+Shift_L			<-- Left shift, uppercase on
+l
-l					<-- ibctf{xk3yl0gg3r-iz-L
+i
-i					<-- ibctf{xk3yl0gg3r-iz-LI
+n
+u
-n					<-- ibctf{xk3yl0gg3r-iz-LIN
-u					<-- ibctf{xk3yl0gg3r-iz-LINU
+x
-x					<-- ibctf{xk3yl0gg3r-iz-LINUX
-Shift_L			<-- Left shift, uppercase off
+minus
-minus				<-- ibctf{xk3yl0gg3r-iz-LINUX-
+m
-m					<-- ibctf{xk3yl0gg3r-iz-LINUX-m
+1
-1					<-- ibctf{xk3yl0gg3r-iz-LINUX-m1
+m
-m					<-- ibctf{xk3yl0gg3r-iz-LINUX-m1m
+1
-1					<-- ibctf{xk3yl0gg3r-iz-LINUX-m1m1
+k
-k					<-- ibctf{xk3yl0gg3r-iz-LINUX-m1m1k
+4
-4					<-- ibctf{xk3yl0gg3r-iz-LINUX-m1m1k4
+t
-t					<-- ibctf{xk3yl0gg3r-iz-LINUX-m1m1k4t
+z
-z					<-- ibctf{xk3yl0gg3r-iz-LINUX-m1m1k4tz
+Shift_L
+bracketright
-bracketright		<-- ibctf{xk3yl0gg3r-iz-LINUX-m1m1k4tz}
-Shift_L
```

