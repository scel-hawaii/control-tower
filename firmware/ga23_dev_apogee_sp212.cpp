#include "ga23_dev_apogee_sp212.h"

void ga23_dev_apogee_sp212_open(void){
    pinMode(_PIN_GA23_APOGEE_SP212_, INPUT);
}

int ga23_dev_apogee_sp212_read(void){
    int v = analogRead(_PIN_GA23_APOGEE_SP212_);
    return v;
}
