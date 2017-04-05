/*******************************
 *
 * File: gg_dev_eeprom_node_address.h
 *
 * Contains prototypes for EEPROM functions
 *
 ******************************/

#include <Arduino.h>
#include <EEPROM.h>

#ifndef GG_DEV_EEPROM_NODE_ADDRESS_H
#define GG_DEV_EEPROM_NODE_ADDRESS_H
void gg_dev_eeprom_node_address_open(void);
uint16_t gg_dev_eeprom_node_address_read(void);
#endif
