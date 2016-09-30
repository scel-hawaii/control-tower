#include "ga_dev_batt.h"

void ga_dev_batt_open(void){
    pinMode(_PIN_GA_BATT_, INPUT);
}

int ga_dev_batt_read_raw(void){
    int value;
    value = analogRead(_PIN_GA_BATT_);
    return value;
}

int ga_dev_batt_read(void){
    int val = 555;

    #ifndef SEN_STUB
    float raw = (float)analogRead(_PIN_GA_BATT_) * (5.0/1023.0);
    val = raw * 1000;
    #endif

    return val;
}
