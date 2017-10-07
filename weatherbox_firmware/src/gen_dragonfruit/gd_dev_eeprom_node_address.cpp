/*******************************
 *
 * File: gd_dev_eeprom_node_address.cpp
 *
 * This module is a driver for the EEPROM used
 * to read the Node ID.
 *
 ******************************/

#include "gd_dev_eeprom_node_address.h"

/******************************
 *
 * Name:        gd_dev_eeprom_node_address_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Nothing (To keep it consistent)
 *
 ******************************/

void gd_dev_eeprom_node_address_open(void){}

/******************************
 *
 * Name:        gd_dev_eeprom_node_address_read
 * Returns:     Nothing
 * Parameter:   Node ID as an integer
 * Description: Read the Node ID from the EEPROM
 *
 ******************************/

uint16_t gd_dev_eeprom_node_address_read(void){
    uint32_t node_addr = EEPROM.read(2) | (EEPROM.read(3)<<8);
    return node_addr;
}

/******************************
 *
 * Name:        gd_dev_eeprom_node_address_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the Node ID
 *              displays it to the Serial Monitor
 *
 ******************************/

void gd_dev_eeprom_node_address_test(void){
    Serial.print(F("[P] node addr: "));
    Serial.println((int) gd_dev_eeprom_node_address_read());
}
