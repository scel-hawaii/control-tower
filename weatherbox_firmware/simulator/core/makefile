all: init base-model

init:
	# Arch linux requires a small patch because it comes with a newer version of GCC.
	# See issue below for info:
	# 	https://github.com/buserror/simavr/issues/131
	sed -i 's/char string\[\]/char string\[128\]/g' simavr/simavr/sim/avr/avr_mcu_section.h
	sed -i 's/char name\[\]/char name\[128\]/g' simavr/simavr/sim/avr/avr_mcu_section.h

	cd simavr && make

	# Reset the mcu_section.h file to get rid of git warnings
	git checkout simavr/simavr/sim/avr/avr_mcu_section.h

base-model:
	cd emu_base_model && make

# Install required packages for debian/ubuntu
install-pkgs-debian:
	sudo apt-get install -y avr-libc libelf-dev freeglut3-dev pkg-config avrdude

clean:

