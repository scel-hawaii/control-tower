#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

//GPS pins
#define _GPS_TX_ 5
#define _GPS_RX_ 4

#ifndef GA_DEV_GPS
#define GA_DEV_GPS

void ga_dev_GPS_open(void);
uint16_t ga_dev_GPS_fix_read(void);
uint16_t ga_dev_GPS_time_read(void);
uint16_t ga_dev_GPS_date_read(void);
uint16_t ga_dev_GPS_lat_read(void);
uint16_t ga_dev_GPS_lon_read(void);

#endif
