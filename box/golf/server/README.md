# Build

```sh
apt install -y libseccomp-dev
make local
docker build -t golf .
docker run -d -p 9000:9000 -it golf
nc localhost 9000
```
