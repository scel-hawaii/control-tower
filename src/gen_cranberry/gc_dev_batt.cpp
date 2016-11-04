#include "gc_dev_batt.h"

static Adafruit_ADS1115 adc;

void gc_dev_batt_open(void){
    adc.begin();
}

uint16_t gc_dev_batt_read(void){
    uint16_t value = 4000;

    #ifndef SEN_STUB
    /* Multiply the result by 2.0 because the ADC is connected to a voltage divider circuit
    that halves the original battery voltage.

    Note: the cranberry v3.5.0 schematic is incorrect because the values for R21 and
    R20 are described with values of 150k and 51k respectively. In reality, R21 and
    R20 are equal to each other (the values are still unkown as of 2016-10-24). */
    value = 2.0*((float)adc.readADC_SingleEnded(2)*188.0)/(1000.0);
    #endif

    return value;
}

void gc_dev_batt_test(void){
    Serial.println(F("[P] Check batt value"));
    uint16_t batt_val = gc_dev_batt_read();

    Serial.print(F("[P] batt value: "));
    Serial.print(batt_val);
    Serial.println(F(" mV"));

    if(batt_val < 0){
        Serial.println(F("[P] \tError: batt out of range"));
    }
}
