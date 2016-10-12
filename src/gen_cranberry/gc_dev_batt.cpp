#include "gc_dev_batt.h"

void gc_dev_batt_open(void){
    pinMode(_PIN_GC_BATT_, INPUT);
}

uint16_t gc_dev_batt_read_raw(void){
  uint16_t val = analogRead(_PIN_GC_BATT_);
  return val;
}

uint16_t gc_dev_batt_read(void){
    float raw = (float)analogRead(_PIN_GC_BATT_) * (5.0/1023.0);
    uint16_t val = raw * 1000;
    return val;
}
