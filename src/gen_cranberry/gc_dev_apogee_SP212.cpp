#include "gc_dev_apogee_SP212.h"

static Adafruit_ADS1115 adc;

void gc_dev_apogee_SP212_open(void){
    adc.begin();
}

uint16_t gc_dev_apogee_SP212_solar_irr_read(void){
    uint16_t value = 4000;

    #ifndef SEN_STUB
    value = ((float)adc.readADC_SingleEnded(0)*188.0)/(1000.0)*(4.0/3.3);
    #endif

    return value;
}
