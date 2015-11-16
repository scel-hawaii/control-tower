/*******************************************
 * 
 *    File: transmit.h
 *    REIS Weatherbox Firmware
 *    
 *    Header file for Transmission functions
 *
 ******************************************/

/* External Libraries */
#include <Xbee.h>

/* Check for previous includes */
#ifndef TRANSMIT_H
#define TRANSMIT_H

/* Macros */
#define MAX_SIZE 200

/* Packet Initialization/Clear */
void Packet_Clear(uint8_t *packet);

/* Transmission Code */
void Packet_Transmit(uint8_t *packet);

/* Test Packet Generation */
void Test_Packet_Gen(uint8_t *packet);
#endif
