FROM openjdk:11-slim-buster
EXPOSE 9000

RUN groupadd -r ctf && useradd --no-log-init -r -g ctf ctf
RUN mkdir game/
WORKDIR game/

COPY TheGame.java .
RUN javac TheGame.java
RUN apt-get update && apt-get install -y socat
CMD ["/usr/bin/socat", "TCP-LISTEN:9000,reuseaddr,fork", "EXEC:\"java TheGame\",pty,rawer,stderr,echo=0,su=ctf"]
