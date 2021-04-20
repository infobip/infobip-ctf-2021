# Build

```sh
make local
docker build -t sig .
docker run -d -p 9000:9000 -it sig
nc localhost 9000
```
