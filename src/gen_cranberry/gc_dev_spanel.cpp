#include "gc_dev_spanel.h"

static Adafruit_ADS1115 adc;

void gc_dev_spanel_open(void){
    adc.begin();
}

int gc_dev_spanel_read(void){
  uint16_t value = 6000;

  #ifndef SEN_STUB
  value = ((float)adc.readADC_SingleEnded(3)*188.0)/(1000.0);
  #endif
  
  return value;
}
