#include "gg_dev_adafruit_GPS.h"

SoftwareSerial GPSpins(16,17); //(16,17)
Adafruit_GPS GPS(&GPSpins);

void gg_dev_adafruit_GPS_open(void){
  // Serial.begin(115200);
  // Serial.println("Setting up GPS");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  delay(1000);
  GPS.read();
}
/*
uint32_t gg_dev_adafruit_GPS_read(void){
  GPS.read();
  uint32_t gg_time = 0;
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return gg_time;
    else{
      Serial.print("\nTime: ");
      gg_time = GPS.hour * 10000;
      Serial.print(gg_time);
      Serial.print(':');
      gg_time = (GPS.minute * 100) + gg_time;
      Serial.print(gg_time);
      Serial.print(':');
      gg_time = GPS.seconds + gg_time;
    }
  }
  return gg_time;
}

uint16_t gg_dev_adafruit_GPS_read(void){
  GPS.read();
  uint16_t gg_time = 0;
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return 0;
    else{
      gg_time = GPS.hour;
      return gg_time;
    }
  }
}

uint16_t gg_dev_adafruit_GPS_min_read(void){
  GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
    if (GPS.fix && GPS.fixquality){
      return GPS.minute;
    }
  }
}
uint16_t gg_dev_adafruit_GPS_sec_read(void){
  GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
    if (GPS.fix && GPS.fixquality){
      return GPS.seconds;
    }
  }
}
uint16_t gg_dev_adafruit_GPS_month_read(void){
  GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
    if (GPS.fix && GPS.fixquality){
      return GPS.month;
    }
  }
}
uint16_t gg_dev_adafruit_GPS_day_read(void){
  GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
    if (GPS.fix && GPS.fixquality){
      return GPS.day;
    }
  }
}
uint16_t gg_dev_adafruit_GPS_year_read(void){
  GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
    if (GPS.fix && GPS.fixquality){
      return GPS.year;
    }
  }
}

uint16_t gg_dev_adafruit_GPS_lat_read(void){
  GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
    if (GPS.fix && GPS.fixquality){
      return GPS.latitude;
    }
  }
}
uint16_t gg_dev_adafruit_GPS_long_read(void){
  GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
    if (GPS.fix && GPS.fixquality){
      return GPS.longitude;
    }
  }
}

void gg_dev_adafruit_GPS_test(void){
      Serial.print("\nTime: ");
      Serial.print(GPS.hour, DEC); Serial.print(':');
      Serial.print(GPS.minute, DEC); Serial.print(':');
      Serial.print(GPS.seconds, DEC); Serial.print('.');
      Serial.println(GPS.milliseconds);
      Serial.print("Date: ");
      Serial.print(GPS.month, DEC); Serial.print('/');
      Serial.print(GPS.day, DEC); Serial.print("/20");
      Serial.println(GPS.year, DEC);
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
}
*/
