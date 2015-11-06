#include "transmit.h"

void Packet_Transmit(uint8_t *packet){
/* Given: A Packet.
   Returns: Nothing.
   Actions: Transmits the packet using the functionality from the
            Arduino Xbee Library
*/
    /* Variable Declarations */
    XBee xbee = XBee();//Create Xbee Object
    int length = 0;    //Length of the packet to be sent
    int i = 0;         //Variable to be used to iterate across the packet

    /* Obtain address of receiving end */
    XBeeAddress64 addr64 = XBeeAddress64(0,0); //!!TEST if this gets right addr

    /* Get length of packet */
    length = strlen((char *) packet); //!!TEST if this gives right length

    /* Debug */
    //printf("Length is %d\n", length);
    Serial.print("\nLength is: ");
    Serial.print(length);

    /* Transfer the packet */
    ZBTxRequest zbTx = ZBTxRequest(addr64, packet, length);
    xbee.send(zbTx);
}

void Test_Packet_Gen(uint8_t *packet){
/* Given: A packet.
   Returns: Nothing.
   Actions: Fills the packet with random data, used for debugging ONLY.
*/

    /* Necessary Variables */
    int i = 0;

    /* Set up packet */
    String s;
    
    /* Fill with random information */
    s = "test yes";
    s += '\0';

    /* Set packet */
    for(i = 0; i < s.length(); i++)
    {
      packet[i] = s[i];
    }
}
