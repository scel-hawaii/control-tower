all:
	platformio run --environment ga_debug

upload:
	platformio run --environment ga_debug --target upload

clean:
	platformio run --target clean
