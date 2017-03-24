/*******************************
 *
 * File: ga_dev_eeprom_node_address.h
 *
 * Contains prototypes for EEPROM functions
 *
 ******************************/

#include <Arduino.h>
#include <EEPROM.h>

#ifndef GA_DEV_EEPROM_NODE_ADDRESS_H
#define GA_DEV_EEPROM_NODE_ADDRESS_H
void ga_dev_eeprom_node_address_open(void);
uint16_t ga_dev_eeprom_node_address_read(void);
#endif
