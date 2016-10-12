#include "gc_dev_sp212.h"

static Adafruit_ADS1115 adc;

void gc_dev_sp212_open(void){
    adc.begin();
}

uint16_t gc_dev_sp212_read(void){
    uint16_t value;
    value = ((float)adc.readADC_SingleEnded(0)*188.0)/(1000.0);
    return value;
}
