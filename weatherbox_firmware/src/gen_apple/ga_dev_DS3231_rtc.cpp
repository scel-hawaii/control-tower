
#include "ga_dev_DS3231_rtc.h"
#include <DS3231.h>

DS3231  rtc(SDA, SCL);

void ga_dev_DS3231_rtc_open(void){
    //Serial.begin(9600);
    rtc.begin();
    //rtc.setDOW(WEDNESDAY);
    //rtc.setDate(1, 1, 2014);
    //rtc.setTime(12, 0, 0);
}

uint32_t ga_dev_DS3231_rtc_date_read(void){ //maybe uint24_t or uint32_t
    //rtc.setDate(1, 1, 2014);
    #ifndef SEN_STUB
    uint32_t value = rtc.getDateStr();
    #endif
    //Serial.println(value);
    return value;

}

uint16_t ga_dev_DS3231_rtc_time_read(void){
    //rtc.setTime(12, 0, 0);
    #ifndef SEN_STUB
    uint16_t value = rtc.getTimeStr();
    #endif
    return value;
}

uint32_t ga_dev_DS3231_rtc_unix_read(void){
  uint32_t value = rtc.getUnixTime(rtc.getTime());
  return value;
}
