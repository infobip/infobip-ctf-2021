# Build

```sh
make local
docker build -t headers .
docker run -d -p 9000:9000 -it headers
nc localhost 9000
```
