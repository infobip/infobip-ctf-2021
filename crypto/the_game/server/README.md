# Build

```sh
docker build -t game .
docker run -d -p 9000:9000 -it game
nc localhost 9000
```
