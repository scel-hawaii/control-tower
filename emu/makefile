all: init base-model

init:
	rm -rf v1.3.tar.gz
	wget https://github.com/buserror/simavr/archive/v1.3.tar.gz
	tar xvf v1.3.tar.gz
	rm v1.3.tar.gz
	mv simavr-1.3 simavr

	# Arch linux requires a small patch because it comes with a newer version of GCC.
	# See issue below for info:
	# 	https://github.com/buserror/simavr/issues/131
	sed -i 's/char string\[\]/char string\[128\]/g' simavr/simavr/sim/avr/avr_mcu_section.h
	sed -i 's/char name\[\]/char name\[128\]/g' simavr/simavr/sim/avr/avr_mcu_section.h

	cd simavr && make

base-model:
	cd emu_base_model && make

# Install required packages for debian/ubuntu
install-pkgs-debian:
	sudo apt-get install -y avr-libc libelf-dev freeglut3-dev pkg-config avrdude

clean:
	rm -rf simavr simavr-1.3 v1.3.tar.gz


