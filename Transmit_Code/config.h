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
 *        - Apple 3.4
 *        - Cranberry 3.2
 *        - Dragonfruit 2.0
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

/* Configuration for Testing */
#define TEST

/* Macros */
#define MAX_SIZE 80

/*-------------------------*/
/*----Generation Config----*/
/*-------------------------*/

/* Generation Declarations: Only define one */
#define APPLE
//#define CRANBERRY
//#define DRAGONFRUIT

/* Apple Pin Configuration */
#ifdef APPLE

    /* Version */
    #define APPLE_VERSION 34

    /* Wind Sensor */
    #define _PIN_ANEMOMETER0 A0
    #define _PIN_ANEMOMETER1 10
    #define _PIN_ANEMOMETER2 11
    #define _PIN_ANEMOMETER3 12

    /* Receiver/Transmitter */
    #define _PIN_RX 0
    #define _PIN_TX 1

    /* XBEE */
    #define _PIN_XBEE_TX 9
    #define _PIN_XBEE_RX 2
    #define _PIN_XBEE_SLEEP 13

    /* Temperature */
    #define _PIN_ROOF_TEMP 3

    /* GPS */
    #define _PIN_GPS_RX 4
    #define _PIN_GPS_TX 5

    /* Sensor On/Off */
    #define _PIN_SEN_EN 6

    /* Humidity */
    #define _PIN_HUMID_CLK 7
    #define _PIN_HUMID_DATA 8
 
    /* Panel and Battery Voltage */
    #define _PIN_SOLAR_V A1
    #define _PIN_BATT_V A3

    /* Solar Irradiance */
    #define _PIN_APOGEE_V A2

    /* I2C */
    #define _PIN_SDA A4
    #define _PIN_SCL A5

    /* Address of Component - Not used */
    #define _ADDR_BARO 0
    #define _ADDR_PYRO 0     //Address of ADC output NOT Pyronometer
    #define _ADDR_HYGRO 0

/* Cranberry Pin Configuration */
#elif defined(CRANBERRY)
   
    /* Version */
    #define CRAN_VERSION 32

    /* Wind Sensor - Currently not implemented */ 
    #define _PIN_ANEMOMETER0 0
    #define _PIN_ANEMOMETER1 0
    #define _PIN_ANEMOMETER2 0
    #define _PIN_ANEMOMETER3 0

    /* Receiver/Transmitter */
    #define _PIN_RX 0
    #define _PIN_TX 1

    /* XBEE */
    #define _PIN_XBEE_TX 8
    #define _PIN_XBEE_RX 2
    #define _PIN_XBEE_EN 3
    #define _PIN_XBEE_DTR A1
    #define _PIN_XBEE_RSSI A2
    #define _PIN_XBEE_SLEEP A3

    /* Sensor On/Off */
    #define _PIN_SEN_EN 4

    /* Panel and Battery Voltage (Pins of ADC) */
    #define _PIN_BATT_V 2
    #define _PIN_SOLAR_V 3

    /* Solar Irradiance (Pins of ADC) */
    #define _PIN_APOGEE_V 0

    /* I2C */
    #define _PIN_SDA A4
    #define _PIN_SCL A5

    /* Address of Component */
    #define _ADDR_BARO 0x60
    #define _ADDR_PYRO 0x48     //Address of ADC output NOT Pyronometer
    #define _ADDR_HYGRO 0x27

/* Dragonfruit Pin Configuration */
#elif defined(DRAGONFRUIT)
    
    /* Version */
    #define DRAGON_VERSION 20

    /* Currently not implemented */ 
    #define _PIN_ANEMOMETER0 0
    #define _PIN_ANEMOMETER1 0
    #define _PIN_ANEMOMETER2 0
    #define _PIN_ANEMOMETER3 0

    /* Receiver/Transmitter */
    #define _PIN_RX 0
    #define _PIN_TX 1

    /* XBEE */
    #define _PIN_XBEE_TX 8
    #define _PIN_XBEE_RX 2
    #define _PIN_XBEE_EN 3
    #define _PIN_XBEE_DTR A1
    #define _PIN_XBEE_RSSI A2
    #define _PIN_XBEE_SLEEP A3

    /* Sensor On/Off */
    #define _PIN_SEN_EN 4
    
    /* Panel and Battery Voltage */
    #define _PIN_SOLAR_V A0
    #define _PIN_BATT_V A7

    /* I2C */
    #define _PIN_SDA A4
    #define _PIN_SCL A5
    
    /* Address of Component */
    #define _ADDR_BARO 0x60
    #define _ADDR_PYRO 0x48     //Address of ADC output NOT Pyronometer
    #define _ADDR_HYGRO 0x27

    /* Debug LEDs */
    #define _PIN_LED1 5
    #define _PIN_LED2 6
    #define _PIN_LED3 7
    #define _PIN_LED4 9
    #define _PIN_LED5 10

    /* Not being used by this gen */
    #define _PIN_APOGEE_V 0
    
#endif

/*-------------------------*/
/*----Function Pointers----*/
/*-------------------------*/

/* Sensors */
//extern void (*Sensors_init)(void);
//extern long (*Sensors_sampleBatterymV)(void);
//extern long (*Sensors_samplePanelmV)(void);
//extern long (*Sensors_sampleSolarIrrmV)(void);
//extern long (*Sensors_samplePressurepa)(void);
//extern long (*Sensors_sampleHumiditypct)(void);
//extern long (*Sensors_sampleTempdecic)(void);

/* Transmit */
//extern void (*Packet_Clear)(void);
//extern void (*Packet_Con)(void);
//extern void (*Packet_Transmit)(void);

/* Routine */
//extern void (*Normal_Routine)(int *count);

/*-------------------------*/
/*-Configuration Functions-*/
/*-------------------------*/
//void Gen_config(void);
//void Transmit_config(void);

#endif
