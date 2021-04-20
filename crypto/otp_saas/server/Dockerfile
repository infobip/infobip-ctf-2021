FROM python:3-alpine
EXPOSE 9000

RUN addgroup -S ctf && adduser -S ctf -G ctf
RUN mkdir otpsaas/
WORKDIR otpsaas/

COPY otpsaas.py .
RUN apk add socat

CMD ["/usr/bin/socat", "TCP-LISTEN:9000,reuseaddr,fork", "EXEC:\"python3 otpsaas.py\",pty,rawer,stderr,echo=0,su=ctf"]
