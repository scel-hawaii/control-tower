#include "gd_dev_spanel.h"

void gd_dev_spanel_open(void){
    pinMode(_PIN_GD_SPANEL_, INPUT);
}

int gd_dev_spanel_read(void){
    int value = 555;

    #ifndef SEN_STUB
    value = analogRead(_PIN_GD_SPANEL_);
    //2*analogRead(_PIN_GD_SPANEL_)*5000.0/1023;
    #endif

    return value;
}

