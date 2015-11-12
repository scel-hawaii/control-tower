/*******************************************
 *
 *    File: transmit.cpp
 *    REIS Weatherbox Firmware
 *
 *    File containing Transmission functions
 *
 ******************************************/


/* Necessary Libraries */
#include "transmit.h"


/******************************************
 *
 *   Name:        Packet_Transmit
 *   Returns:     Nothing
 *   Parameter:   uint8_t *packet
 *   Description: Transmits using Arduino Xbee functions,
 *                    Xbees must be in API mode.
 *
 *****************************************/
void Packet_Transmit(uint8_t *packet){

    /* Variable Declarations */
    XBee xbee = XBee();    //Create Xbee Object
    int length = 0;        //Length of the packet to be sent
    int i = 0;             //Variable to be used to iterate across the packet

    /* Obtain address of receiving end */
    XBeeAddress64 addr64 = XBeeAddress64(0,0); //!!TEST if this gets right addr

    /* Get length of packet */
    length = strlen((char *) packet);

    /* Debug */
    Serial.print("\nLength is: ");
    Serial.print(length);

    /* Transfer the packet */
    ZBTxRequest zbTx = ZBTxRequest(addr64, packet, length);
    xbee.send(zbTx);
}

/******************************************
 *
 *   Name:        Test_Packet_Gen
 *   Returns:     Nothing
 *   Parameter:   uint8_t *packet
 *   Description: Constructs a packet with hard-coded
 *                    information.  Used for the initial
 *                    test of the Transmission functions.
 *                    To be replaced by Packet Construction.
 *
 *****************************************/
void Test_Packet_Gen(uint8_t *packet){

    /* Necessary Variables */
    int i = 0;

    /* Set up array */
    String s;
    
    /* Fill with Hard-coded information */
    s = "test yes";
    s += '\0';

    /* Put array information into Packet */
    for(i = 0; i < s.length(); i++)
    {
      packet[i] = s[i];
    }
}
