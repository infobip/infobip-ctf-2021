# Solution

To solve, one needs to find out that the protocol used is CoAP.

Afterwards, the task is easy - one needs to use any language and a CoAP client library to connect to the server and solve the addition challenge. Solution is written as `client.go` (you might need to copy it to server folder to work).

```
$ go run client.go 
2020/11/13 15:44:27 ! VERIFICATION REQUIRED BEFORE PROCEEDING !

Please note that the challenge is linked to your token.
Challenge is revoked in 5 seconds.

What is 2596996162 + 4039455774?
Your token is: f37d767452177f5c
Send your answer as PUT message with 32 bit big endian unsigned integer in payload
2020/11/13 15:44:27 Verified. Here you go: ibctf{i0t-sh0ws-u-the_M0N3YY}
```
