.PHONY: all
all:

.PHONY: integration
integration:
	docker-compose build
	docker-compose up --abort-on-container-exit --exit-code-from gateway

