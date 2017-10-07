#!/bin/bash
# Runs the base model so you can manually program the emulated device if
# you want to.

ELF_PATH=emu_base_model/obj-*/emu_base_model.elf
IHEX_PATH=emu_base_model/*.ihex

# Execute the ELF file, giving the IHEX bootloader path. Must be run in the emu/ directory
# to work properly.
./$ELF_PATH $IHEX_PATH
