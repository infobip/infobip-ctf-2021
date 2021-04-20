# Build

```sh
make local
docker build -t iot .
docker run -d -p 8443:8443 -it iot
```
