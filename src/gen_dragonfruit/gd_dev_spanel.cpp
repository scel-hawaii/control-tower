#include "gd_dev_spanel.h"

void gd_dev_spanel_open(void){
    pinMode(_PIN_GD_SPANEL_, INPUT);
}

int gd_dev_spanel_read(void){
    int value = 555;

    #ifndef SEN_STUB
    value = digitalRead(_PIN_GD_SPANEL_);
    #endif

    return value;
}
