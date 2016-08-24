#include "ga23_dev_spanel.h"

void ga23_dev_spanel_open(void){
    pinMode(_PIN_GA23_SPANEL_, INPUT);
}

int ga23_dev_spanel_read(void){
    int value = digitalRead(_PIN_GA23_SPANEL_);
    return value;
}
