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

/* Packet Initialization/Clear */
void Packet_ClearUART(uint8_t *packet);
void Packet_ClearBIN(schema_3 *packet);

/* Paacket Construction */
void Packet_ConUART(uint8_t *packet);
void Packet_ConBIN(schema_3 *packet);

/* Transmission Code */
void Packet_TransmitUART(uint8_t *packet);
void Packet_TransmitBIN(schema_3 *packet);

/* Test Packet Generation */
void Test_Packet_GenUART(uint8_t *packet);
void Test_Packet_GenBIN(schema_3 *packet);
#endif
