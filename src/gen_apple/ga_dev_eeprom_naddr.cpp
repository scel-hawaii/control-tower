/*******************************
 *
 * File: ga_dev_eeprom_naddr.cpp
 *
 * This module is a driver for the EEPROM
 * containing the node ID
 *
 ******************************/

#include "ga_dev_eeprom_naddr.h"

void ga_dev_eeprom_naddr_open(void){}

uint16_t ga_dev_eeprom_naddr_read(void){
    uint32_t node_addr = EEPROM.read(2) | (EEPROM.read(3)<<8);
    return node_addr;
}
