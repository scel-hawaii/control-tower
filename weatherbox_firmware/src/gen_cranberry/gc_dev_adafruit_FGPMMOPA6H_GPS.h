/*******************************
 *
 * File: gc_dev_adafruit_FGPMMOPA6H_GPS.h
 *
 * Contains prototypes for GPS sensor functions
 *
 ******************************/
#ifndef GC_DEV_FGPMMOPA6H
#define GC_DEV_FGPMMOPA6H

#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>


// boolean usingInterrupt = false;
// void useInterrupt(boolean);
void gc_dev_adafruit_GPS_open(void);
uint8_t gc_dev_adafruit_GPS_longitude(void);
uint8_t gc_dev_adafruit_GPS_latitude(void);
uint8_t gc_dev_adafruit_GPS_altitude(void);
void gc_dev_adafruit_GPS_test(void);

#endif
