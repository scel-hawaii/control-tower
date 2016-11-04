#include "gc_dev_honeywell_HIH6131.h"
#include "HIH613x.h"

static HIH613x hih6131(0x27);

void gc_dev_honeywell_HIH6131_open(void){
    Wire.begin(9600);
}


uint16_t gc_dev_honeywell_HIH6131_temp_centik_read(void){
    int16_t value = 30000;

    #ifndef SEN_STUB
    hih6131.update();
    value = (float)hih6131.getTemperature()*100.0 + 27315.0;
    #endif

    return value;
}

uint16_t gc_dev_honeywell_HIH6131_humidity_pct_read(void){
    uint16_t value = 60;

    #ifndef SEN_STUB
    hih6131.update();
    value = hih6131.getHumidity();
    #endif

    return value;
}

void gc_dev_honeywell_HIH6131_temp_centik_test(void){
    Serial.println(F("[P] Check hih6131_temp_centik value"));
    int hih6131_temp_centik_val = gc_dev_honeywell_HIH6131_temp_centik_read();

    Serial.print(F("[P] hih6131_temp_centik value: "));
    Serial.print(hih6131_temp_centik_val);
    Serial.println(F(" cK"));

    if(hih6131_temp_centik_val < 0){
        Serial.println(F("[P] \tError: hih6131 temp out of range"));
    }
}

void gc_dev_honeywell_HIH6131_humidity_pct_test(void){
    Serial.println(F("[P] Check hih6131_humidity value"));
    int hih6131_humidity_pct_val = gc_dev_honeywell_HIH6131_humidity_pct_read();

    Serial.print(F("[P] hih6131_humidity_pct value: "));
    Serial.print(hih6131_humidity_pct_val);
    Serial.println(F("\%"));

    if(hih6131_humidity_pct_val < 0){
        Serial.println(F("[P] \tError: hih6131 humidity out of range"));
    }
}
