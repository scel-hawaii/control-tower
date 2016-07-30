#include "ga23_dev_bmp085.h"
static Adafruit_BMP085 bmp085;

void ga23_dev_bmp085_open(void){
    bmp085.begin();
}

int ga23_dev_bmp085_read(void){
    int value = bmp085.readPressure();
    return value;
}

float ga23_dev_bmp085_read_temp(void){
    float value = bmp085.readTemperature();
    return value;
}
