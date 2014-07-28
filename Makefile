INSTALL_DIR='/usr/local/control_tower'
CURRENT_DIR=$(shell pwd)
LATEST_VERSION=$(shell git describe --abbrev=0 --tags)

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
	
