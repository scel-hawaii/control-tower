/*******************************
 *
 * File: gg_dev_eeprom_node_address.cpp
 *
 * This module is a driver for the EEPROM
 * containing the node ID
 *
 ******************************/

#include "gg_dev_eeprom_node_address.h"

/******************************
 *
 * Name:        gg_dev_eeprom_node_address_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Nothing (To keep it consistent)
 *
 ******************************/

void gg_dev_eeprom_node_address_open(void){}

/******************************
 *
 * Name:        gg_dev_eeprom_node_address_read
 * Returns:     Nothing
 * Parameter:   Node ID as an integer
 * Description: Read the Node ID from the EEPROM
 *
 ******************************/

uint16_t gg_dev_eeprom_node_address_read(void){
    uint32_t node_addr = EEPROM.read(2) | (EEPROM.read(3)<<8);
    return node_addr;
}
