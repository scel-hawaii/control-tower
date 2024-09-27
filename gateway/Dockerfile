FROM python:3

ADD requirements.txt /
ADD setup_venv.sh /
RUN ./setup_venv.sh

COPY . /gateway
WORKDIR /gateway

ENV PYTHONUNBUFFERED = 1
ENTRYPOINT ["/env/bin/python", "server.py"]