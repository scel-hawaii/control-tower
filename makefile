all:
	platformio run

upload:
	platformio run --target upload

clean:
	platformio run --target clean
