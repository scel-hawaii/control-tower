#include "gd_dev_adafruit_MPL115A2_press.h"
#include "Adafruit_MPL115A2.h"

static Adafruit_MPL115A2 mpl115a2t1_press;

void gd_dev_adafruit_MPL115A2_press_open(void){
    mpl115a2t1_press.begin();
}

uint16_t gd_dev_adafruit_MPL115A2_press_read(void){
  uint16_t value = 0;
  #ifndef SEN_STUB
  value = mpl115a2t1_press.getPressure()*1000;
  #endif
  return value;
}
