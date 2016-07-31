/*********************************************
 *
 *    File: REIS_Weatherbox.ino
 *    REIS Weatherbox Firmware
 *
 *    The main driver file for the REIS Weatherbox
 *
 ********************************************/

#include <EEPROM.h>

/* Program Libraries */
#include "config.h"
#include "sensors.h"
#include "transmit.h"
#include "schema.h"
#include "utilities.h"
#include "routines.h"
#include "log.h"
#include "mod_cmd_mode.h"
#include "ga23_board.h"

/* Arudino Libraries */
#include <Wire.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

/* External Libraries */
#include <SHT1x.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_MPL115A2.h>
#include <Adafruit_ADS1015.h>
#include <HIH613x.h>
#include <XBee.h>


#ifdef GA23
#else
/* Global Xbee object */
XBee G_xbee = XBee();

#ifdef APPLE
schema_7 G_BINpacket;
#elif defined(CRANBERRY) || defined(DRAGONFRUIT)
schema_3 G_BINpacket;
#endif

/* Global for Filters */
LowPassFilter G_solar_filter;
LowPassFilter G_battery_filter;

/* Global Variable */
int G_count;

/* Global Function Pointers */
void (*Sensors_init)(void);
long (*Sensors_sampleBatterymV)(void);
long (*Sensors_samplePanelmV)(void);
long (*Sensors_sampleSolarIrrmV)(void);
long (*Sensors_samplePressurepa)(void);
long (*Sensors_sampleHumiditypct)(void);
long (*Sensors_sampleTempdecic)(void);
void (*Packet_Clear)(void);
void (*Packet_Con)(void);
void (*Packet_Transmit)(void);
void (*Normal_Routine)(int *count);

/* Software Serial */
SoftwareSerial mySerial(_PIN_XBEE_RX, _PIN_XBEE_TX);
#endif

#ifdef GA23
struct ga23_board board;
#endif

/*********************************************
 *
 *    Name:        setup
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Runs once at the start of the sequence.
 *                     Used for initialization. Place all
 *                     init scripts here.
 *
 ********************************************/
void setup(){
#ifdef GA23
    ga23_board_init(&board);
    board.print_build_opts();
    board.setup(&board);
    board.post();

    #ifdef _BCFG_ONLY_POST
    // Stop execution if the ONLY_POST build configuration
    // flag is defined.
    while(1);
    #endif

#else
    Serial.begin(9600);
    mySerial.begin(9600);
    print_log("POST Start");

    /* Variable Initialization */
    G_count = 0;

    /* Generation Check */
    Gen_config();

    /* Transmission Method Check */
    Transmit_config();

    /* Initialization */
    Sensors_init();
    G_xbee.begin(mySerial);

    /* Packet Initialization */
    Packet_Clear();

    /* Set Power State */
    pstate_system(_ACTIVE);

    print_log("POST Complete");

    /* Delay for configuration settings */
    delay(500);
#endif
}

/*********************************************
 *
 *    Name:        loop
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Main program function, runs constantly.
 *                     Executed after setup(), and will
 *                     continue running indefinitely,
 *                     unless conditions stop it.
 *
 ********************************************/
void loop(){
#ifdef GA23
    while(1){
        if(board.ready_sample(&board))  board.sample(&board);
        if(board.ready_tx(&board))      board.tx(&board);
        if(board.ready_run_cmd(&board))      board.run_cmd(&board);
    }
#else
    long last_sample_ms = 0;
    long wait_ms = 1000;
    while(1){
        if( (millis() - last_sample_ms ) >= wait_ms){
            last_sample_ms = millis();
            Normal_Routine(&G_count);
        }
        cmd_mode_check();
    }
#endif

}
