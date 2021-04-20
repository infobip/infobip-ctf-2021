# Don't forget to execute
# echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
# on target host to disable ASLR
FROM ubuntu:16.04
EXPOSE 9000

RUN apt-get update -y && apt-get install -y \
    lib32z1 \
    xinetd \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m ctf

WORKDIR /ctf

RUN echo "Connection blocked" > /etc/banner_fail
COPY ctf.xinetd /etc/xinetd.d/ctf
COPY flag.txt .
COPY poperet .
COPY start.sh .

RUN chmod -R 755 /ctf

ENTRYPOINT []
CMD ["/usr/sbin/xinetd", "-dontfork"]
