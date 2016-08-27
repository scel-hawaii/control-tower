#include "ga_dev_batt.h"

void ga_dev_batt_open(void){
    pinMode(_PIN_GA_BATT_, INPUT);
}

int ga_dev_batt_read(void){
    int val = analogRead(_PIN_GA_BATT_);
    return val;
}
