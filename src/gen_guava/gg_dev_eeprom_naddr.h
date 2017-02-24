/*******************************
 *
 * File: gg_dev_eeprom_naddr.h 
 *
 * Contains prototypes for EEPROM functions
 *
 ******************************/

#include <Arduino.h>
#include <EEPROM.h>

#ifndef gg_DEV_EEPROM_NADDR_H
#define gg_DEV_EEPROM_NADDR_H
void gg_dev_eeprom_naddr_open(void);
uint16_t gg_dev_eeprom_naddr_read(void);
#endif
