FROM python:3-alpine
EXPOSE 9000

RUN addgroup -S ctf && adduser -S ctf -G ctf
RUN mkdir console/
WORKDIR console/

COPY console.py ./console.py
COPY totally-not-guessable-flag.txt ./totally-not-guessable-flag.txt

RUN apk add socat
CMD ["/usr/bin/socat", "TCP-LISTEN:9000,reuseaddr,fork", "EXEC:\"python3 console.py\",pty,rawer,stderr,echo=0,su=ctf"]
