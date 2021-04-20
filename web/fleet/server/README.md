# Build

```sh
docker build -t fleet .
docker run -d -p 8080:8080 -it fleet
curl http://localhost:8080
```
