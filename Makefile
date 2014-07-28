INSTALL_DIR='/usr/local/control_tower'
CURRENT_DIR=$(shell pwd)
LATEST_VERSION=$(shell git describe --abbrev=0 --tags)
version:
	echo $(CURRENT_VERSION)
install:
	$(shell git checkout $(LATEST_VERSION))
	cp -vfR $(CURRENT_DIR)/* $(INSTALL_DIR)
	ln -fs /usr/local/control_tower/control_tower.py /usr/local/bin/control_tower
	
