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

/* Debug with Arduino Serial Monitor */
//#define DEBUG_S

/*-------------------------*/
/*---Transmission Config---*/
/*-------------------------*/

/* Transmission method declarations: only define one */
//#define UART
#define BINARY

/* Macros */
#define MAX_SIZE 250

/*-------------------------*/
/*----Generation Config----*/
/*-------------------------*/

/* Generation Declarations: Only define one */
#define APPLE
//#define CRANBERRY
//#define DRAGONFRUIT

/* Apple Pin Configuration */
#ifdef APPLE

    #define APPLE_VERSION 34

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
#elif defined(CRANBERRY)

/* Dragonfruit Pin Configuration */
#elif defined(DRAGONFRUIT)
    
    #define DRAGON_VERSION 10

/* Currently not implemented 
    #define _PIN_ANEMOMETER0 
    #define _PIN_ANEMOMETER1 
    #define _PIN_ANEMOMETER2 
    #define _PIN_ANEMOMETER3 
*/
    #define _PIN_RX 0
    #define _PIN_TX 1

    #define _PIN_XBEE_TX 2
    #define _PIN_XBEE_RX 8
    #define _PIN_XBEE_EN 3
    #define _PIN_XBEE_DTR A1
    #define _PIN_XBEE_RSSI A2
    #define _PIN_XBEE_SLEEP A3

    #define _PIN_SEN_EN 4

    #define _PIN_SDA A4
    #define _PIN_SCL A5

    #define _PIN_LED1 5
    #define _PIN_LED2 6
    #define _PIN_LED3 7
    #define _PIN_LED4 9
    #define _PIN_LED5 10

#endif

/*-------------------------*/
/*----Function Pointers----*/
/*-------------------------*/

/* Sensors */
extern void (*Sensors_init)(void);
extern int (*Sensors_sampleBatterymV)(void);
extern int (*Sensors_samplePanelmV)(void);
extern int (*Sensors_sampleSolarIrrmV)(void);
extern int (*Sensors_samplePressurepa)(void);
extern int (*Sensors_sampleHumiditypct)(void);
extern int (*Sensors_sampleTempdecic)(void);

/* Transmit */
//extern void (*Packet_Clear)(void);
//extern void (*Packet_Con)(void);
//extern void (*Packet_Transmit)(void);

/* Routine */
//extern void (*Normal_Routine)(int *count);

/*-------------------------*/
/*-Configuration Functions-*/
/*-------------------------*/
void Gen_config(void);
//void Transmit_config(void);

#endif
