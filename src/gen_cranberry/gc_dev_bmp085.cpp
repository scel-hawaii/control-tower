#include "gc_dev_bmp085.h"
static Adafruit_BMP085 bmp085;

void gc_dev_bmp085_open(void){
    bmp085.begin();
}

uint32_t gc_dev_bmp085_read(void){
    uint32_t value = bmp085.readPressure();
    return value;
}

uint16_t gc_dev_bmp085_read_temp(void){
    float value_f = bmp085.readTemperature();
    uint16_t value = value_f * 10;
    return value;
}
