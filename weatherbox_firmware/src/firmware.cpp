/*********************************************
 *
 *    File: firmware.cpp
 *    SCEL Weatherbox Firmware
 *
 *    The main driver file for the SCEL Weatherbox
 *
 ********************************************/

#ifdef GA
#include "gen_apple/ga_board.h"
#elif defined(GG)
#include "gen_guava/gg_board.h"
#endif

/* Arudino Libraries */
#include <Wire.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <SPI.h>

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
#include <Adafruit_BME280.h>

#ifdef GA
struct ga_board board;
#endif

#ifdef GG
struct gg_board board;
#endif

void setup(){
    #ifdef GA
    ga_board_init(&board);
    #endif

    #ifdef GG
    gg_board_init(&board);
    #endif

    board.print_build_opts();
    board.setup(&board);
    board.post();
}

void loop(){
    if(board.ready_sample(&board))  board.sample(&board);
    if(board.ready_tx(&board))      board.tx(&board);
    if(board.ready_run_cmd(&board))      board.run_cmd(&board);
    if(board.ready_heartbeat_tx(&board))      board.heartbeat_tx(&board);
}
