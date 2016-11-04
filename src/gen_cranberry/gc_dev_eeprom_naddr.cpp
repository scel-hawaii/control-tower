#include "gc_dev_eeprom_naddr.h"

void gc_dev_eeprom_naddr_open(void){}

uint16_t gc_dev_eeprom_naddr_read(void){
    uint32_t node_addr = EEPROM.read(2) | (EEPROM.read(3)<<8);
    return node_addr;
}

void gc_dev_eeprom_naddr_test(void){
    Serial.print(F("[P] node addr: "));
    Serial.println((int) gc_dev_eeprom_naddr_read());
}
