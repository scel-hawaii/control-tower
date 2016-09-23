#include "ga_dev_spanel.h"

void ga_dev_spanel_open(void){
    pinMode(_PIN_GA_SPANEL_, INPUT);
}

int ga_dev_spanel_read(void){
    int value = 555;

    #ifndef SEN_STUB
    value = analogRead(_PIN_GA_SPANEL_);
    #endif

    return value;
}
