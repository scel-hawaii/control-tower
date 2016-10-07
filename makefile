all:
	platformio run 

upload:
	platformio run --environment ga_production --target upload

clean:
	platformio run --target clean
