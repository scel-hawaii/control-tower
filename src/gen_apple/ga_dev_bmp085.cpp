#include "ga_dev_bmp085.h"
static Adafruit_BMP085 bmp085;

void ga_dev_bmp085_open(void){
    bmp085.begin();
}

uint32_t ga_dev_bmp085_read_press(void){
    uint32_t value = 80;

    #ifndef SEN_STUB
    value = bmp085.readPressure();
    #endif

    return value;
}

int16_t ga_dev_bmp085_read_temp(void){
    int16_t value = 89;

    #ifndef SEN_STUB
    float value_f = bmp085.readTemperature();
    value = value_f * 10;
    #endif

    return value;
}
