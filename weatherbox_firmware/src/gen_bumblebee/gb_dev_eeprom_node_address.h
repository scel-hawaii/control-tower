/*******************************
 *
 * File: gb_dev_eeprom_node_address.h
 *
 * Contains prototypes for EEPROM functions
 *
 ******************************/

#include <Arduino.h>
#include <EEPROM.h>

#ifndef GB_DEV_EEPROM_NODE_ADDRESS_H
#define GB_DEV_EEPROM_NODE_ADDRESS_H
void gb_dev_eeprom_node_address_open(void);
uint16_t gb_dev_eeprom_node_address_read(void);
#endif
