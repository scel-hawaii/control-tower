#include "gc_dev_hih6131.h"
#include "HIH613x.h"

static HIH613x hih6131(0x27);

void gc_dev_hih6131_open(void){
    Wire.begin(9600);
}

uint16_t gc_dev_hih6131_temp_centik_read(void){
    int16_t value = 30000;

    #ifndef SEN_STUB
    hih6131.update();
    value = (float)hih6131.getTemperature()*100.0 + 27315.0;
    #endif

    return value;
}

uint16_t gc_dev_hih6131_humidity_pct_read(void){
    uint16_t value = 60;

    #ifndef SEN_STUB
    hih6131.update();
    value = hih6131.getHumidity();
    #endif

    return value;
}
