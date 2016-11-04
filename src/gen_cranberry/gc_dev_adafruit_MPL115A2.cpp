#include "gc_dev_adafruit_MPL115A2.h"
#include "Adafruit_MPL115A2.h"

static Adafruit_MPL115A2 mpl115a2;

void gc_dev_adafruit_MPL115A2_open(void){
    mpl115a2.begin();
}

uint32_t gc_dev_adafruit_MPL115A2_press_pa_read(void){
    uint32_t value = 100000;

    #ifndef SEN_STUB
    value = mpl115a2.getPressure() * 1000;
    #endif

    return value;
}

void gc_dev_adafruit_MPL115A2_press_pa_test(void){
    Serial.println(F("[P] Check mpl115a2t1_press_pa value"));
    uint32_t mpl115a2t1_press_pa_val = gc_dev_adafruit_MPL115A2_press_pa_read();

    Serial.print(F("[P] mpl115a2t1_press_pa value: "));
    Serial.print(mpl115a2t1_press_pa_val);
    Serial.println(F(" Pa"));

    if(mpl115a2t1_press_pa_val < 0){
        Serial.println(F("[P] \tError: mpl115a2t1 pressure out of range"));
    }
}
