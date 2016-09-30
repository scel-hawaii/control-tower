#include "ga_dev_spanel.h"

void ga_dev_spanel_open(void){
    pinMode(_PIN_GA_SPANEL_, INPUT);
}

int ga_dev_spanel_read(void){
    int value = 555;

    #ifndef SEN_STUB
    value = 2.0*(float)analogRead(_PIN_GA_SPANEL_)*(5000.0/1023.0)+(70.0);
    #endif

    return value;
}
