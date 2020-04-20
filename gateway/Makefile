SHELL := /bin/bash
.PHONY: test

all:

init: requirements.txt
	./setup_venv.sh

test:
	source ./env/bin/activate; \
	pytest --rootdir test;


