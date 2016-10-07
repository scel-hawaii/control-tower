#!/bin/bash

ELF_PATH=emu_base_model/obj-*/emu_base_model.elf
IHEX_PATH=emu_base_model/*.ihex

# Execute the ELF file, giving the IHEX bootloader path. Must be run in the emu/ directory
# to work properly.
./$ELF_PATH $IHEX_PATH
