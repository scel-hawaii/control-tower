/*******************************************
 * 
 *    File: transmit.h
 *    REIS Weatherbox Firmware
 *    
 *    Header file for Transmission functions
 *
 ******************************************/

/* Program Libraries */
#include "schema.h"
#include "config.h"
//#include "sensors.h"
//#include "utilities.h"

/* External Libraries */
#include <EEPROM.h>
#include <XBee.h>
#include <overflow_checker.h>

/* Check for previous includes */
#ifndef TRANSMIT_H
#define TRANSMIT_H

/* Global Variable for Packet  */
extern uint8_t G_UARTpacket[MAX_SIZE];

/* Global XBee object */
extern XBee G_xbee;

#ifdef APPLE
extern schema_2 G_BINpacket;
#elif defined(CRANBERRY) || defined(DRAGONFRUIT)
extern schema_1 G_BINpacket;
#endif

/* Packet Initialization/Clear */
void Packet_ClearUART(void);
void Packet_ClearBIN(void);

/* Paacket Construction */
void Packet_ConUART(void);
void Packet_ConBIN(void);

/* Transmission Code */
void Packet_TransmitUART(void);
void Packet_TransmitBIN(void);

/* Test Packet Generation */
void Test_Packet_GenUART(void);
void Test_Packet_GenBIN(void);
#endif
