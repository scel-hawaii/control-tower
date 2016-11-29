#include "gc_dev_apogee_SP212.h"

static Adafruit_ADS1115 adc;

void gc_dev_apogee_SP212_open(void){
    adc.begin();
}

uint16_t gc_dev_apogee_SP212_solar_irr_read(void){
    uint16_t value = 4000;

    #ifndef SEN_STUB
    value = ((float)adc.readADC_SingleEnded(0)*188.0)/(1000.0);
    #endif

    return value;
}

void gc_dev_apogee_SP212_solar_irr_test(void){
    Serial.println(F("[P] Check apogee_sp212 value"));
    int apogee_sp212_val = gc_dev_apogee_SP212_solar_irr_read();

    Serial.print(F("[P] apogee_sp212 solar irr value: "));
    Serial.print(apogee_sp212_val);
    Serial.println(F(" mV"));

    if(apogee_sp212_val < 0){
        Serial.println(F("[P] \tError: apogee solar irr out of range"));
    }
}
