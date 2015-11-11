/*******************************************
 *
 *    File: config.h
 *    REIS Weatherbox Firmware
 *    
 *    Configuration file to initialize the appropriate
 *        functions, variables, and pins that correspond
 *        to the Generation to which this code will be
 *        programmed onto.
 *
 *    Current Configuration Options:
 *        - Apple 2.3
 *        - Cranberry 1.0
 *        - Dragonfruit 1.0
 *
 ******************************************/

/* Check for previous includes */
#ifndef CONFIG_H
#define CONFIG_H

/* Generation Declarations: Only Uncomment ONE generation */
#define APPLE
//#define CRANBERRY
//#define DRAGONFRUIT

/* Apple Pin Configuration */
#ifdef APPLE

    #define APPLE_VERSION 23

    #define _PIN_ANEMOMETER0 A0
    #define _PIN_ANEMOMETER1 10
    #define _PIN_ANEMOMETER2 11
    #define _PIN_ANEMOMETER3 12

    #define _PIN_RX 0
    #define _PIN_TX 1

    #define _PIN_XBEE_TX 0
    #define _PIN_XBEE_RX 1
    #define _PIN_XBEE_SLEEP 13

    #define _PIN_AMB_TEMP 2
    #define _PIN_ROOF_TEMP 3

    #define _PIN_GPS_RX 4
    #define _PIN_GPS_TX 5

    #define _PIN_PSWITCH 6

    #define _PIN_HUMID_CLK 7
    #define _PIN_HUMID_DATA 8

    #define _PIN_SOLAR_V A1
    #define _PIN_APOGEE_V A2
    #define _PIN_BATT_V A3
    #define _PIN_SDA A4
    #define _PIN_SCL A5

/* Cranberry Pin Configuration */
#elif CRANBERRY

/* Dragonfruit Pin Configuration */
#elif DRAGONFRUIT
#endif


/* Function Pointers */
void (*Sensors_init)(void);
int (*Sensors_sampleBatterymV)(void);
int (*Sensors_samplePanelmV)(void);
int (*Sensors_sampleSolarIrrmV)(void);
int (*Sensors_samplePressurepa)(void);
int (*Sensors_sampleHumiditypct)(void);
int (*Sensors_sampleTempdecic)(void);

/* Configuration Function */
void Gen_config(void);

#endif
