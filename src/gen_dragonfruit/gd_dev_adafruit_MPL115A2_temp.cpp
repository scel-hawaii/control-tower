#include "gd_dev_adafruit_MPL115A2_temp.h"
#include "Adafruit_MPL115A2.h"

static Adafruit_MPL115A2 mpl115a2t1;

void gd_dev_adafruit_MPL115A2_temp_open(void){
    mpl115a2t1.begin();
}

int32_t gd_dev_adafruit_MPL115A2_temp_read(void){
  int32_t value = 0;
  #ifndef SEN_STUB
  value = mpl115a2t1.getTemperature()*10;
  #endif
  return value;
}
