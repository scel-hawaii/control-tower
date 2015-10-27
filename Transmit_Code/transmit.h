/* Necessary Libraries */
#include <Xbee.h>

/* Check for previous includes */
#ifndef TRANSMIT_H
#define TRANSMIT_H

/* Transmission Code */
void Packet_Transmit(uint8_t *packet);

/* Test Packet Generation */
void Test_Packet_Gen(uint8_t *packet);
#endif
