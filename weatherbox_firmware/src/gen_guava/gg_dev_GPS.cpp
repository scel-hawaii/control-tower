#include "gg_dev_GPS.h"

// define GPS pins
SoftwareSerial GPSpins(_GPS_TX_,_GPS_RX_);
Adafruit_GPS GPS(&GPSpins);

// Global variables to keep the last known GPS signals
uint16_t last_lat_gg = 0;
uint16_t last_lon_gg = 0;

// initialize GPS board
void gg_dev_GPS_open(void){
  GPS.begin(9600); // baud rate of 9600
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // turn on recommended minimum and fix data
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // set rate to 1Hz
  delay(1000);
  GPS.read();
}

uint16_t gg_dev_GPS_fix_read(void){
  uint16_t fix = 0;

  if(GPS.fix){
    fix = 1;
  }
  return fix;
}

/**********************************************
*
* Name:         gg_dev_GPS_time_read
* Returns:      unsigned int
* Parameter:    nothing
* Description:  returns the time using RTC
*               in format HHMMSS
*
***********************************************/
uint16_t gg_dev_GPS_time_read(void){
  uint16_t time_gg;
  GPS.read();
    if(GPS.newNMEAreceived()){
      Serial.println("in the loop");
      if (GPS.parse(GPS.lastNMEA())){
        time_gg = GPS.hour * 10000;
        time_gg = (GPS.minute * 100) + time_gg;
        time_gg = GPS.seconds + time_gg;
        return time_gg;
      }
    }
  return time_gg = 0;
}

/**********************************************
*
* Name:         gg_dev_GPS_time_read
* Returns:      unsigned int
* Parameter:    nothing
* Description:  returns the date using RTC
*               in format MMDDYY
*
***********************************************/
uint16_t gg_dev_GPS_date_read(void){
  GPS.read();
  uint16_t date_gg = 0;
  date_gg = GPS.month * 10000;
  date_gg = (GPS.day * 100) + date_gg;
  date_gg = GPS.year + date_gg;

  return date_gg;
}

/**********************************************
*
* Name:         gg_dev_GPS_lat_read
* Returns:      unsigned int
* Parameter:    nothing
* Description:  returns the latitude using GPS
*
***********************************************/
uint16_t gg_dev_GPS_lat_read(void){
  uint16_t lat_gg = 0;
  GPS.read();
  if(GPS.fix){
    lat_gg = GPS.latitude;
    last_lat_gg = lat_gg;
  }
  else{
    lat_gg = last_lat_gg;
  }

  return lat_gg;
}

/**********************************************
*
* Name:         gg_dev_GPS_lon_read
* Returns:      unsigned int
* Parameter:    nothing
* Description:  returns the longitude using GPS
*
***********************************************/
uint16_t gg_dev_GPS_lon_read(void){
  uint16_t lon_gg = 0;
  if(GPS.fix){
    lon_gg = GPS.longitude;
    last_lon_gg = lon_gg;
  }
  else{
    lon_gg = last_lon_gg;
  }

  return lon_gg;
}
