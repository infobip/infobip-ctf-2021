# Build

```sh
apt install maven
cd fleet_rest/
mvn package spring-boot:repackage
cp target/*.jar ../fleet.jar
cd ..
docker build -t fleetrest .
docker run -d -p 8080:8080 -it fleetrest
curl http://localhost:8080
```
