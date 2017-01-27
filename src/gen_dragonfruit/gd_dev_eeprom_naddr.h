/*******************************
 *
 * File: gd_dev_eeprom_naddr.h 
 *
 * Contains prototypes for eeprom functions 
 *
 ******************************/

#include <Arduino.h>
#include <EEPROM.h>

#ifndef GD_DEV_EEPROM_NADDR_H
#define GD_DEV_EEPROM_NADDR_H
void gd_dev_eeprom_naddr_open(void);
uint16_t gd_dev_eeprom_naddr_read(void);
#endif
