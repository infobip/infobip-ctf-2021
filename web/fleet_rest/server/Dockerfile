FROM openjdk:11

RUN groupadd -r ctf && useradd --no-log-init -r -g ctf ctf

RUN mkdir web/ && chown ctf:ctf web/
WORKDIR web

COPY fleet.jar ./fleet.jar
USER ctf
CMD ["java", "-jar", "fleet.jar"]
