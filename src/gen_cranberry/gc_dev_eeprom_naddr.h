#include <Arduino.h>
#include <EEPROM.h>

#ifndef GC_DEV_EEPROM_NADDR_H
#define GC_DEV_EEPROM_NADDR_H
void gc_dev_eeprom_naddr_open(void);
uint16_t gc_dev_eeprom_naddr_read(void);
void gc_dev_eeprom_naddr_test(void);
#endif
