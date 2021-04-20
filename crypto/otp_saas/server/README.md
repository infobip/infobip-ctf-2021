# Build

```sh
docker build -t otpsaas .
docker run -d -p 9000:9000 -it otpsaas
nc localhost 9000
```
