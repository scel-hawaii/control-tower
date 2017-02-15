#include "gg_dev_spanel.h"

void gg_dev_spanel_open(void){
    pinMode(_PIN_gg_SPANEL_, INPUT);
}

int gg_dev_spanel_read(void){
    int value = 555;

    #ifndef SEN_STUB
    value = 2.0*(float)analogRead(_PIN_gg_SPANEL_)*(5000.0/1023.0)+(70.0);
    #endif

    return value;
}
