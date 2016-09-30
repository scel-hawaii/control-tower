#include "gd_dev_batt.h"

void gd_dev_batt_open(void){
    pinMode(_PIN_GD_BATT_, INPUT);
}

int gd_dev_batt_read(void){
    int value = 555;

    #ifndef SEN_STUB
    value = analogRead(_PIN_GD_BATT_);
    #endif

    return value;
}

