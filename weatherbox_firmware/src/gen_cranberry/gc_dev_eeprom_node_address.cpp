/*******************************
 *
 * File: gc_dev_eeprom_node_address.cpp
 *
 * This module is a driver for the EEPROM used
 * to read the Node ID.
 *
 ******************************/

#include "gc_dev_eeprom_node_address.h"

/******************************
 *
 * Name:        gc_dev_eeprom_node_address_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Nothing (To keep it consistent)
 *
 ******************************/

void gc_dev_eeprom_node_address_open(void){}

/******************************
 *
 * Name:        gc_dev_eeprom_node_address_read
 * Returns:     Nothing
 * Parameter:   Node ID as an integer
 * Description: Read the Node ID from the EEPROM
 *
 ******************************/

uint16_t gc_dev_eeprom_node_address_read(void){
    uint32_t node_addr = EEPROM.read(2) | (EEPROM.read(3)<<8);
    return node_addr;
}

/******************************
 *
 * Name:        gc_dev_eeprom_node_address_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the Node ID
 *              displays it to the Serial Monitor
 *
 ******************************/

void gc_dev_eeprom_node_address_test(void){
    Serial.print(F("[P] node addr: "));
    Serial.println((int) gc_dev_eeprom_node_address_read());
}
