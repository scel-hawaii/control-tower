#include "gc_dev_apogee_sp212.h"

void gc_dev_apogee_sp212_open(void){
    pinMode(_PIN_GC_APOGEE_SP212_, INPUT);
}

int gc_dev_apogee_sp212_read(void){
    int v = analogRead(_PIN_GC_APOGEE_SP212_);
    return v;
}
