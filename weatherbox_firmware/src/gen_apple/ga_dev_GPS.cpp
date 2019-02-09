#include "ga_dev_GPS.h"

// define GPS pins
SoftwareSerial GPSpins(_GPS_TX_,_GPS_RX_);
Adafruit_GPS GPS(&GPSpins);

// Global variables to keep the last known GPS signals
uint16_t last_lat_ga = 0;
uint16_t last_lon_ga = 0;

// initialize GPS board
void ga_dev_GPS_open(void){
  GPS.begin(9600); // baud rate of 9600
  pinMode(_GPS_TX_,OUTPUT);
  pinMode(_GPS_RX_,INPUT);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // turn on recommended minimum and fix data
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // set rate to 1Hz
  delay(1000);
  GPS.read();
}

uint16_t ga_dev_GPS_fix_read(void){
  uint16_t fix = 0;
Serial.println(GPS.fix);
  if(GPS.fix){
    fix = 1;
  }
  return fix;
}

/**********************************************
*
* Name:         ga_dev_GPS_time_read
* Returns:      unsigned int
* Parameter:    nothing
* Description:  returns the time using RTC
*               in format HHMMSS
*
***********************************************/
uint16_t ga_dev_GPS_time_read(void){
  uint16_t time_ga;
  GPS.read();
    if(GPS.newNMEAreceived()){
      Serial.println("in the loop");
      if (GPS.parse(GPS.lastNMEA())){
        time_ga = GPS.hour * 10000;
        time_ga = (GPS.minute * 100) + time_ga;
        time_ga = GPS.seconds + time_ga;
        return time_ga;
      }
    }
  return time_ga = 0;
}

/**********************************************
*
* Name:         ga_dev_GPS_time_read
* Returns:      unsigned int
* Parameter:    nothing
* Description:  returns the date using RTC
*               in format MMDDYY
*
***********************************************/
uint16_t ga_dev_GPS_date_read(void){
  GPS.read();
  uint16_t date_ga = 0;
  date_ga = GPS.month * 10000;
  date_ga = (GPS.day * 100) + date_ga;
  date_ga = GPS.year + date_ga;

  return date_ga;
}

/**********************************************
*
* Name:         ga_dev_GPS_lat_read
* Returns:      unsigned int
* Parameter:    nothing
* Description:  returns the latitude using GPS
*
***********************************************/
uint16_t ga_dev_GPS_lat_read(void){
  uint16_t lat_ga = 0;
  GPS.read();
  if(GPS.fix){
    lat_ga = GPS.latitude;
    last_lat_ga = lat_ga;
  }
  else{
    lat_ga = last_lat_ga;
  }

  return lat_ga;
}

/**********************************************
*
* Name:         ga_dev_GPS_lon_read
* Returns:      unsigned int
* Parameter:    nothing
* Description:  returns the longitude using GPS
*
***********************************************/
uint16_t ga_dev_GPS_lon_read(void){
  uint16_t lon_ga = 0;
  if(GPS.fix){
    lon_ga = GPS.longitude;
    last_lon_ga = lon_ga;
  }
  else{
    lon_ga = last_lon_ga;
  }

  return lon_ga;
}
