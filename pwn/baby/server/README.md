Build

```sh
make local
docker build -t baby .
docker run -d -p 9000:9000 -it baby
nc localhost 9000
```
