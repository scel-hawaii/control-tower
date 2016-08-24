#include "ga23_dev_batt.h"

void ga23_dev_batt_open(void){
    pinMode(_PIN_GA23_BATT_, INPUT);
}

int ga23_dev_batt_read(void){
    int val = analogRead(_PIN_GA23_BATT_);
    return val;
}
