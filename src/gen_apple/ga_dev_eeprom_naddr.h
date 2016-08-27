#include <Arduino.h>
#include <EEPROM.h>

#ifndef GA_DEV_EEPROM_NADDR_H
#define GA_DEV_EEPROM_NADDR_H
void ga_dev_eeprom_naddr_open(void);
uint16_t ga_dev_eeprom_naddr_read(void);
#endif
