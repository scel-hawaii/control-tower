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

/* External Libraries */
#include <EEPROM.h>
#include <XBee.h>

/* Check for previous includes */
#ifndef TRANSMIT_H
#define TRANSMIT_H

/* Macros */
#define MAX_SIZE 250

/* Method of Transfer ONLY set one to True (Potentially move to config.h) */
//#define UART
#define BINARY

/* Debug with Serial Monitor */
#define DEBUG_S

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
