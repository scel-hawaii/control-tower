#include "gc_dev_mpl115a2t1.h"
#include "Adafruit_MPL115A2.h"

static Adafruit_MPL115A2 mpl115a2;

void gc_dev_mpl115a2t1_open(void){
    mpl115a2.begin();
}

int gc_dev_mpl115a2t1_press_kpa_read(void){
    uint16_t value = 80;

    #ifndef SEN_STUB
    value = mpl115a2.getPressure();
    #endif

    return value;
}
