#include <Arduino.h>
#include <EEPROM.h>

#ifndef GA23_DEV_EEPROM_NADDR_H
#define GA23_DEV_EEPROM_NADDR_H
void ga23_dev_eeprom_naddr_open(void);
uint16_t ga23_dev_eeprom_naddr_read(void);
#endif
