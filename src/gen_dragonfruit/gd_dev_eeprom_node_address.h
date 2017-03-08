/*******************************
 *
 * File: gd_dev_eeprom_node_address.h
 *
 * Contains prototypes for reading the node ID
 * from the EEPROM
 *
 ******************************/

#include <Arduino.h>
#include <EEPROM.h>

#ifndef gd_DEV_EEPROM_NODE_ADDRESS_H
#define gd_DEV_EEPROM_NODE_ADDRESS_H
void gd_dev_eeprom_node_address_open(void);
uint16_t gd_dev_eeprom_node_address_read(void);
void gd_dev_eeprom_node_address_test(void);
#endif
