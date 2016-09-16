#include "gc_dev_spanel.h"

void gc_dev_spanel_open(void){
    pinMode(_PIN_GC_SPANEL_, INPUT);
}

int gc_dev_spanel_read(void){
    int value = digitalRead(_PIN_GC_SPANEL_);
    return value;
}
