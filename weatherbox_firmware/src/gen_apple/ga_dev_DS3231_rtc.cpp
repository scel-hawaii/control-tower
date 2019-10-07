
#include "ga_dev_DS3231_rtc.h"
#include "DS3231.h"

DS3231  rtc(SDA, SCL);

void ga_dev_DS3231_rtc_open(void){
    rtc.begin();
}

uint16_t ga_dev_DS3231_rtc_date_read(void){
    #ifndef SEN_STUB
    uint16_t value = rtc.getDateStr();
    #endif
    //return value;
}

uint16_t ga_dev_DS3231_rtc_time_read(void){
    #ifndef SEN_STUB
    uint16_t value = rtc.getTimeStr();
    #endif
    //return value;
}

uint32_t ga_dev_DS3231_rtc_unix_read(void){
  //ga_dev_DS3231_rtc_date_read();
  //ga_dev_DS3231_rtc_time_read();
  uint32_t value;
  #ifndef SEN_STUB
  value = rtc.getUnixTime(rtc.getTime());
  #endif
  return value;
}
