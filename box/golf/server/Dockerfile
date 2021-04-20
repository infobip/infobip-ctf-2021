# Don't forget to execute
# echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
# on target host to disable ASLR
FROM ubuntu:16.04
EXPOSE 9000

RUN groupadd -r ctf && useradd --no-log-init -r -g ctf ctf
RUN mkdir chall/
WORKDIR chall/

COPY golf .
COPY flag.txt .
RUN chmod +x ./golf
RUN chmod +r ./flag.txt
RUN apt-get update && apt-get install -y socat
CMD ["/usr/bin/socat", "TCP-LISTEN:9000,reuseaddr,fork", "EXEC:\"./golf\",pty,rawer,stderr,echo=0,su=ctf"]
