# Weatherbox

General firmware for the [SCEL weatherbox data collection platform](https://wiki.scel-hawaii.org/doku.php?id=weatherbox:start).
This is a re-write of the [old weatherbox firmware](https://github.com/scel-hawaii/weatherbox-firmware-old).

# Current Contributors

* Kenny Luong
* Dylan Tokia
* Allie Kim
* Nathan Lam

# Previous Contributors

* Ryan Walser (Fall 2015 - Spring 2016)
* Scott Nakashima (Fall 2015 - Spring 2016)

# Build Instructions

To build, run:

```
platformio run                  # build all targets
platformio run -e env_name      # build a specific target
```

See [platformio.ini](platformio.ini) for platform specific environments.

**Note:** Builds are supported through platformio, but verification and validation tests may need a
linux based operating system to run properly. If you aren't using a linux-based OS, you can
Vagrant and VirtualBox to provision a virtual machine on your local computer.

After installing Vagrant and Virtualbox, run:

```
vagrant up

```

Once the installation is complete, run `vagrant SSH` in the project directory to connect
to the virutal machine.



# Contributing

See the github flow for more information: https://guides.github.com/introduction/flow/

1. Create a new branch
2. Do some development
3. Finish development
4. Submit a pull request (we will do a code review together)

# Warnings

* Do NOT commit to the master branch, always use your own branch

