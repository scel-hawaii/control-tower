#include "gd_dev_adafruit_MPL115A2_temp.h"
#include "Adafruit_MPL115A2.h"

static Adafruit_MPL115A2 mpl115a2t1;

void gd_dev_adafruit_MPL115A2_temp_open(void){
    mpl115a2t1.begin();
}

uint16_t gd_dev_adafruit_MPL115A2_temp_read(void){
  uint16_t value = 0;
  float raw_value;
  #ifndef SEN_STUB
  raw_value = mpl115a2t1.getTemperature(); //Function returns floating point value in Celcius
  value = ((raw_value + 273.15) * 100); //Convert to centiKelvin (cK)
  #endif
  return (uint16_t)value;
}
