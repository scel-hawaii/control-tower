/*********************************************
 *
 *    File: firmware.cpp
 *    SCEL Weatherbox Firmware
 *
 *    The main driver file for the SCEL Weatherbox
 *
 ********************************************/

#include <EEPROM.h>

/* Program Libraries */
#include "log.h"

#ifdef GA
#include "gen_apple/ga_board.h"
#elif defined(GC)
#include "gen_cranberry/gc_board.h"
#elif defined(GD)
#include "gen_dragonfruit/gd_board.h"
#elif defined(GG)
#include "gen_guava/gg_board.h"
#endif

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

#ifdef GA
struct ga_board board;
#endif

#ifdef GC
struct gc_board board;
#endif

#ifdef GD
struct gd_board board;
#endif

#ifdef GG
struct gg_board board;
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
    #ifdef GA
    ga_board_init(&board);
    #endif

    #ifdef GC
    gc_board_init(&board);
    #endif

    #ifdef GD
    gd_board_init(&board);
    #endif

    #ifdef GG
    gg_board_init(&board);
    #endif

    board.print_build_opts();
    board.setup(&board);
    board.post();

    #ifdef _BCFG_ONLY_POST
    // Stop execution if the ONLY_POST build configuration
    // flag is defined.
    while(1);
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
    if(board.ready_sample(&board))  board.sample(&board);
    if(board.ready_tx(&board))      board.tx(&board);
    if(board.ready_run_cmd(&board))      board.run_cmd(&board);
    if(board.ready_heartbeat_tx(&board))      board.heartbeat_tx(&board);
}
