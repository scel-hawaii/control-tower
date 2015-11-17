/*********************************
 *
 *    File: packet.h
 *    REIS Weatherbox Firmware
 *    
 *    Header file for packet organization functions
 *
**********************************/

/* Necessary Libraries */
#include <Adafruit_BMP085.h>
#include <Adafruit_INA219.h>
#include <DallasTemperature.h>

/* Create packet object */
schema_3 packet;

/* Binary Packet Organization */
void clear_packet(void); 
void samplePacketBinary(void);

/* UART Packet Organization */
void samplePacketUART(void);

