#include "gc_dev_spanel.h"

void gc_dev_spanel_open(void){
    pinMode(_PIN_GC_SPANEL_, INPUT);
}

int gc_dev_spanel_read_raw(void){
    int val = analogRead(_PIN_GC_SPANEL_);
    return val;
}

int gc_dev_spanel_read(void){
    float raw = (float)analogRead(_PIN_GC_SPANEL_) * (5.0/1023.0) * 2.0;
    int val = raw * 1000;
    return val;
}
