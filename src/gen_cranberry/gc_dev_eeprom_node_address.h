/*******************************
 *
 * File: gc_dev_eeprom_node_address.h
 *
 * Contains prototypes for reading the node ID
 * from the EEPROM
 *
 ******************************/

#include <Arduino.h>
#include <EEPROM.h>

#ifndef GC_DEV_EEPROM_NODE_ADDRESS_H
#define GC_DEV_EEPROM_NODE_ADDRESS_H
void gc_dev_eeprom_node_address_open(void);
uint16_t gc_dev_eeprom_node_address_read(void);
void gc_dev_eeprom_node_address_test(void);
#endif
