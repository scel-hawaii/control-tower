INSTALL_DIR='/usr/local/control_tower'
CURRENT_DIR=$(shell pwd)
LATEST_VERSION=$(shell git describe --abbrev=0 --tags)

help:
	@echo "These makefile commands are available:"
	@echo ""
	@echo "seed - seed the database"
	@echo "db_export - export the database as a CSV file"
	@echo "db_import - import to the database from a CSV file"
	@echo ""

seed:
	bash tasks/seed.sh

export_db:
	bash tasks/export_db_to_csv.sh

import_db:
	bash tasks/import_db_to_csv.sh

version:
	@echo $(LATEST_VERSION)
	@echo $(SUDO_USER)

install:
	@echo "Installing Control Tower."
	@echo "Latest version: $(LATEST_VERSION)"
	sudo -u $(SUDO_USER) git fetch
	sudo -u $(SUDO_USER) git checkout $(LATEST_VERSION)
	rm -rf $(INSTALL_DIR)
	mkdir -p $(INSTALL_DIR)
	cp -fR $(CURRENT_DIR)/* $(INSTALL_DIR)
	ln -fs /usr/local/control_tower/control_tower.py /usr/local/bin/control_tower

test:
	bash tasks/test.sh

run-container:
	docker build -t control-tower-test .
	docker run -d --name ct-testinstance -p 16906:16906 -t control-tower-test

kill-container:
	docker kill ct-testinstance
	docker rm ct-testinstance
