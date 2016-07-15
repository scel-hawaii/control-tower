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
#include "sensors.h"
#include "utilities.h"

/* External Libraries */
#include <EEPROM.h>
#include <XBee.h>

/* Check for previous includes */
#ifndef TRANSMIT_H
#define TRANSMIT_H

/* Global XBee object */
extern XBee G_xbee;

#ifdef APPLE
extern schema_7 G_BINpacket;
#elif defined(CRANBERRY) || defined(DRAGONFRUIT)
extern schema_3 G_BINpacket;
#endif

/* Packet Initialization/Clear */
void Packet_ClearBIN(void);

/* Paacket Construction */
void Packet_ConBIN(void);

/* Transmission Code */
void Packet_TransmitBIN(void);

/* Test Packet Generation */
void Test_Packet_GenBIN(void);
#endif
