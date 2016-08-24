all:
	platformio run --environment ga23_debug

upload:
	platformio run --environment ga23_debug --target upload

clean:
	platformio run --target clean
