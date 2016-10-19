#include "gc_dev_batt.h"

static Adafruit_ADS1115 adc;

void gc_dev_batt_open(void){
    adc.begin();
}

uint16_t gc_dev_batt_read(void){
    uint16_t value = 4000;

    #ifndef SEN_STUB
    value = ((float)adc.readADC_SingleEnded(2)*188.0)/(1000.0);
    #endif

    return value;
}
