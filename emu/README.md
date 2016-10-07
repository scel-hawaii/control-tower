This is a small simavr-based emulator that allows you to quickly test
firmware builds for the weatherbox firmware.

**To setup the emulator**

    make init

This will download v1.3 of simavr, build it as well as the cooresponding base model.
Make sure you have the following dependencies installed:

* avr-libc
* libelf-dev
* freeglut3-dev
* pkg-config

**To the run emulator and load a specific build**

    python run_emu.py ga_stub   # you can specify any other build here

The python script will automatically collect serial output from the device that is
currently under emulation. More interactivity (and possibly a UI) will be added in a later
patch.

