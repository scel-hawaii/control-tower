
#include "ga_dev_rtc.h"


RTC_Millis rtc;

void ga_dev_rtc_open(void){
    rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
}

uint32_t ga_dev_rtc_unix_read(void){

  uint32_t value;
  DateTime now = rtc.now();
  value = now.unixtime();
  return value;
}
