#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

//GPS pins
#define _GPS_TX_ 10
//16

#define _GPS_RX_ 11 
//17

#ifndef GG_DEV_GPS
#define GG_DEV_GPS

void gg_dev_GPS_open(void);
uint16_t gg_dev_GPS_fix_read(void);
uint16_t gg_dev_GPS_time_read(void);
uint16_t gg_dev_GPS_date_read(void);
uint16_t gg_dev_GPS_lat_read(void);
uint16_t gg_dev_GPS_lon_read(void);
#endif
