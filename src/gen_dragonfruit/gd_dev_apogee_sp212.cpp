#include "gd_dev_apogee_sp212.h"

void gd_dev_apogee_sp212_open(void){
    pinMode(_PIN_GD_APOGEE_SP212_, INPUT);
}

int gd_dev_apogee_sp212_read(void){
    int value = 555;
    #ifndef SEN_STUB
    value = analogRead(_PIN_GD_APOGEE_SP212_);
    #endif
    return value;
}
