#include "gd_dev_adafruit_MPL115A2_press.h"
#include "Adafruit_MPL115A2.h"

static Adafruit_MPL115A2 mpl115a2t1_press;

void gd_dev_adafruit_MPL115A2_press_open(void){
    mpl115a2t1_press.begin();
}

uint32_t gd_dev_adafruit_MPL115A2_press_read(void){
  float value = 88;
  #ifndef SEN_STUB
  /* getPressure returns pressure value in kPa.
     Multiply by 1000 to convert to Pa. */
  value = mpl115a2t1_press.getPressure()*1000; 
  #endif
  return (uint32_t)value;
}
