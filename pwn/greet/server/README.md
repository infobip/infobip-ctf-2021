# Build

```sh
make local
docker build -t greet .
docker run -d -p 9000:9000 -it greet
nc localhost 9000
```
