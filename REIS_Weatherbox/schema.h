/*******************************************
 *
 *    File: schema.h
 *    REIS Weatherbox Firmware
 *
 *    Description: This file contains the structure for our packet schema.
 *        The packet schema keeps all of the variables for the functions which
 *        we'll send to the XBee API to be transmitted.
 *
 *    Notes: When a new packet schema is made, create a new structure.
 *        BINARY packet is position dependent on where everything is placed
 *        and sent.
 *
 ******************************************/

/* External Libraries */
#include <stdint.h>

/* Check for previous includes */
#ifndef SCHEMA_H
#define SCHEMA_H

/* Struct for Binary packet transfer */
typedef struct {
    uint16_t schema = 1;             //Schema ID number
    uint16_t address;		 //Address of Arduino
    uint32_t uptime_ms;		 //Time since the start of program
    uint8_t overflow_num;	 //Number of times function millis() overflowed
    uint8_t n;			 //Number of data points in packet (0...30)
    uint16_t batt_mv[15];	 //Battery voltage (millivolts)
    uint16_t panel_mv[15];	 //Panel voltage (millivolts)
    uint32_t bmp085_press_pa;	 //Pressure value (pascals)
    int16_t bmp085_temp_decic;   //Temperature value (celsius)
    uint16_t humidity_centi_pct; //Humidity value (centi-pascals)
    uint16_t apogee_w_m2[60];    //Solar Irradiance (millivolts)
} schema_1;

/* Struct for Apple's packet, contains additional temperatures */
typedef struct {
    uint16_t schema = 2;             //Schema ID number
    uint16_t address;		 //Address of Arduino
    uint32_t uptime_ms;		 //Time since the start of program
    uint8_t overflow_num;	 //Number of times function millis() overflowed
    uint8_t n;			 //Number of data points in packet (0...30)
    uint16_t batt_mv[15];	 //Battery voltage (millivolts)
    uint16_t panel_mv[15];	 //Panel voltage (millivolts)
    uint32_t bmp085_press_pa;	 //Pressure value (pascals)
    int16_t bmp085_temp_decic;   //Temperature value (celsius)
    uint16_t humidity_centi_pct; //Humidity value (centi-pascals)
    uint16_t apogee_w_m2[60];    //Solar Irradiance (millivolts)
    int16_t dallas_roof_c[15];   //Outside temperature value (celcius)
} schema_2;


/* Struct for Health Check */
typedef struct {
	uint16_t schema;	//Schema ID number
	uint16_t address;	//ADdress of Arduino
	uint32_t uptime_ms;	//Time since the start of program
	uint16_t batt_mv;	//Battery voltage (millivolts)
} schema_5;

typedef schema_5 schema_health;
#endif
