#include "gc_dev_spanel.h"

static Adafruit_ADS1115 adc;

void gc_dev_spanel_open(void){
    adc.begin();
}

uint16_t gc_dev_spanel_read(void){
  uint16_t value = 6000;

  #ifndef SEN_STUB
  value = ((float)adc.readADC_SingleEnded(3)*188.0)/(1000.0);
  #endif

  return value;
}

void gc_dev_spanel_test(void){
    Serial.println(F("[P] check panel sensor value"));

    uint16_t spanel_val = gc_dev_spanel_read();
    Serial.print(F("[P] spanel value: "));
    Serial.print(spanel_val);
    Serial.println(F(" mV"));

    if(spanel_val < 100){
        Serial.println(F("[P] \tERROR: spanel value out of range"));
    }
}
