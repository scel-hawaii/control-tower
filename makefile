all:
	platformio run --environment ga_production

upload:
	platformio run --environment ga_production --target upload

clean:
	platformio run --target clean
