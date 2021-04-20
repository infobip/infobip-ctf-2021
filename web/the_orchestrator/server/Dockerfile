FROM python:3-slim-buster

RUN apt-get update && apt-get upgrade -y
RUN groupadd -r ctf && useradd --no-log-init -r -g ctf ctf

RUN mkdir app && chown ctf:ctf app/
WORKDIR app
COPY static ./static
COPY templates ./templates
COPY app.py ./app.py
RUN pip3 install Flask gunicorn requests pyyaml

USER ctf
ENV FLAG="ibctf{st1ll_H4Z-th3-s4m3-py1ssuezz}"
CMD ["gunicorn", "-w", "4", "-b", "0.0.0.0:8080", "app:app"]
