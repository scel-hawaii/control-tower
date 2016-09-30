#include "gc_dev_ads1115.h"

static Adafruit_ADS1115 PyroADC_C;

void gc_dev_solar_open(void){

}

uint16_t gc_dev_solar_read(void){
    uint16_t value;
    value = PyroADC_C.readADC_SingleEnded(1)*0.1875;
    return value;
}
