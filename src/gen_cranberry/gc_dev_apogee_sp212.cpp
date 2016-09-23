#include "gc_dev_apogee_sp212.h"

void gc_dev_apogee_sp212_open(void){
    pinMode(_PIN_GC_APOGEE_SP212_, INPUT);
}

int gc_dev_apogee_sp212_read_raw(void){
    int v;
    v = analogRead(_PIN_GC_APOGEE_SP212_);
    return v;
}

int gc_dev_apogee_sp212_read(void){
    float raw = (float)analogRead(_PIN_GC_APOGEE_SP212_) * (5.0/1023.0);
    int val = raw * 1000;
    return val;
}
