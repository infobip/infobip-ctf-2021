FROM python:3-slim-buster

RUN apt-get update && apt-get upgrade -y
RUN groupadd -r ctf && useradd --no-log-init -r -g ctf ctf

RUN mkdir app && chown ctf:ctf app/
WORKDIR app
COPY pyjwt ./pyjwt
COPY jwt-rs256.key ./jwt-rs256.key
COPY jwt-rs256.pub ./jwt-rs256.pub
COPY app.py ./app.py
COPY flag.txt ./flag.txt
WORKDIR /
RUN pip3 install Flask cryptography gunicorn
RUN pip3 install /app/pyjwt
WORKDIR app

USER ctf
ENV FLAG="ibctf{jwt_vulns-4r3-0ld_but-SSTI-n0p3}"
CMD ["gunicorn", "-w", "4", "-b", "0.0.0.0:8080", "app:app"]
