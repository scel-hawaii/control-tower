/*******************************
 *
 * File: gb_dev_eeprom_node_address.cpp
 *
 * This module is a driver for the EEPROM
 * containing the node ID
 *
 ******************************/

#include "gb_dev_eeprom_node_address.h"

void gb_dev_eeprom_node_address_open(void){}

uint16_t gb_dev_eeprom_node_address_read(void){
    uint32_t node_addr = EEPROM.read(2) | (EEPROM.read(3)<<8);
    return node_addr;
}
