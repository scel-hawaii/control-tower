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
#include "log.h"
#include "gen_apple23/ga23_board.h"

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
        if(board.ready_heartbeat_tx(&board))      board.heartbeat_tx(&board);
    }
#endif

}
