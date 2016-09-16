#include "gc_dev_batt.h"

void gc_dev_batt_open(void){
    pinMode(_PIN_GC_BATT_, INPUT);
}

int gc_dev_batt_read(void){
    int val = analogRead(_PIN_GC_BATT_);
    return val;
}
