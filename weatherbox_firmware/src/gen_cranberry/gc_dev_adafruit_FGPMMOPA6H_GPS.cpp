/*******************************
 *
 * File: gc_dev_adafruit_FGPMMOPA6H_GPS.cpp
 *
 * This module is a driver for the FGPMMOPA6H device using
 * the MT3339 Chipset.
 *
 * Product page: https://www.adafruit.com/product/790
 * Datasheet: https://cdn-shop.adafruit.com/datasheets/GlobalTop-FGPMMOPA6H-Datasheet-V0A.pdf
 *
 ******************************/

#include "gc_dev_adafruit_FGPMMOPA6H_GPS.h"

//Debug
SoftwareSerial mySerial(3,2);
Adafruit_GPS gps(&mySerial);

/******************************
 *
 * Name:        gc_dev_adafruit_GPS_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initializes GPS sensor
 *
 ******************************/
void gc_dev_adafruit_GPS_open(void){

  gps.begin(115200);
  gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  gps.sendCommand(PGCMD_ANTENNA);
  //useInterrupt(true);

}


/******************************
 *
 * Name:        gc_dev_adafruit_longitude
 * Returns:     Longitude value in Degrees
 * Parameter:   Nothing
 * Description: Reads gps data
 *
 ******************************/

uint8_t gc_dev_adafruit_GPS_longitude(void){

uint8_t value;

#ifndef SEN_STUB
  if (gps.newNMEAreceived()){
    gps.parse(gps.lastNMEA());
  }
      if(gps.fix){
        value = gps.longitudeDegrees, 4;
      }
      else{
        Serial.print("Waiting for fix...");
      }
#endif
  return value;
}

/******************************
 *
 * Name:        gc_dev_adafruit_latitude_read
 * Returns:     Latitude value in Degrees
 * Parameter:   Nothing
 * Description: Reads gps data
 *
 ******************************/

uint8_t gc_dev_adafruit_GPS_latitude(void){

uint8_t value;

#ifndef SEN_STUB
   if (gps.newNMEAreceived()){
     gps.parse(gps.lastNMEA());
  }
      if(gps.fix){
        value = gps.latitudeDegrees;
      }
      else{
        Serial.print("Waiting for fix...");
      }
#endif

return value;
}
/******************************
 *
 * Name:        gc_dev_adafruit_altitude_read
 * Returns:     Altitude value in meters
 * Parameter:   Nothing
 * Description: Reads gps data
 *
 ******************************/

uint8_t gc_dev_adafruit_GPS_altitude(void){

uint8_t value;

#ifndef SEN_STUB
     if (gps.newNMEAreceived()){
       gps.parse(gps.lastNMEA());
     }
       if(gps.fix){
    //Converting gps altitude in CM to M
        value = gps.altitude / 100;
      }
      else{
        Serial.print("Waiting for fix...");
      }
#endif
  return value;
}
/******************************
 *
 * Name:        gc_dev_adafruit_GPS_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the
 *              sensor and displays the sample to Serial Monitor
 *
 ******************************/

void gc_dev_adafruit_GPS_test(void){

      Serial.println(F("[gps] Check fgpmmopa6h_gps"));
      if (gps.newNMEAreceived()){
        gps.parse(gps.lastNMEA());
      }
        if(gps.fix){
        Serial.print("Latitude:");
          Serial.print(gps.latitudeDegrees, 4);
          Serial.print("Longitude:");
          Serial.println(gps.longitudeDegrees, 4);
          Serial.print("altitude:");
           Serial.println(gps.altitude);
         }
         else{
         Serial.print("Waiting for fix...");
        }
}
