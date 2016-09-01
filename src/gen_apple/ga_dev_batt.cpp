#include "ga_dev_batt.h"

void ga_dev_batt_open(void){
    pinMode(_PIN_GA_BATT_, INPUT);
}

int ga_dev_batt_read(void){
    int value = 555;

    #ifndef SEN_STUB
    value = analogRead(_PIN_GA_BATT_);
    #endif

    return value;
}
