# Build

```sh
make local
docker build -t poperet .
docker run -d -p 9000:9000 -it poperet
nc localhost 9000
```
