#include "gc_dev_hih6131.h"
#include "HIH613x.h"

static HIH613x hih6131(0x27);

void gc_dev_hih6131_open(void){
    //Investigate need for PINMODE or if address given
    //above is enough.
}

int gc_dev_hih6131_temp_decic_read(void){
    int16_t value = 89;

    #ifndef SEN_STUB
    value = hih6131.getTemperature();
    #endif

    return value;
}

int gc_dev_hih6131_humidity_pct_read(void){
    uint16_t value = 60;

    #ifndef SEN_STUB
    value = hih6131.getHumidity();
    #endif

    return value;
}
