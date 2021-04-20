FROM ubuntu
EXPOSE 8443

RUN groupadd -r ctf && useradd --no-log-init -r -g ctf ctf
RUN mkdir chall/
WORKDIR chall/

COPY build/out .
RUN chmod +x ./out
USER ctf
CMD ["/chall/out"]
