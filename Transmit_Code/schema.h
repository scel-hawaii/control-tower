<<<<<<< HEAD
/*******************************
 *
 *    File: schema.h
 *    REIS Weatherbox Firmware
 *    
 *    Header file containing structure for packet schema
 *
********************************/

/* For now, only schema_3 is included, as the main schema for packets  */

/* Necessary Libraries */
#include <stdint.h>

/* Main schema definition */
=======
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
#include <stdint.h>  //Check if truly needed 

/* Check for previous includes */
#ifndef SCHEMA_H
#define SCHEMA_H

/* Struct for Binary packet transfer */
>>>>>>> 9305bb232d931829aece2cb4c703066432b5d1b3
typedef struct {
    
    /* Identification information */
    uint16_t schema;             //Schema ID number
    uint16_t address;		 //Address of Arduino
    
    /* Overflow flags */
    uint8_t overflow_num;	 //Number of times function millis() overflowed

    /* Data variables */
    uint8_t n;			 //Number of data points in packet (0...30)
    uint16_t batt_mv[6];	 //Battery voltage (millivolts)
    uint16_t panel_mv[6];	 //Panel voltage (millivolts)
    uint16_t bmp085_temp_decic;	 //Temperature value (celsius)
    uint16_t humidity_centi_pct; //Humidity value (centi-pascals)
    uint16_t apogee_w_m2[20];    //Solar Irradiance (millivolts)
    uint32_t uptime_ms;		 //Time since the start of program
    uint32_t bmp085_press_pa;	 //Pressure value (pascals)

} schema_3;
#endif
