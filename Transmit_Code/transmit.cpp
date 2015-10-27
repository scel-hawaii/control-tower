#include "transmit.h"

void Packet_Transmit(uint8_t *packet){
/* Given: A Packet.
   Returns: Nothing.
   Actions: Transmits the packet using the functionality from the
            Arduino Xbee Library
*/
    /* Variable Declarations */
    int length = 0;    //Length of the packet to be sent
    int i = 0;         //Variable to be used to iterate across the packet

    /* Obtain address of receiving end */
    XBeeAddress64 addr64 = XBeeAddress64(0,0); //!!TEST if this gets right addr

    /* Get length of packet */
    length = sizeof(packet); //!!TEST if this gives right length

    /* Debug */
    printf("Length is %d\n", length);

    /* Transfer the packet */
    //ZBTxRequest zbTx = ZBTxRequest(addr64, packet, length);
    //xbee.send(zbTx);
}

void Test_Packet_Gen(uint8_t *packet){
/* Given: A packet.
   Returns: Nothing.
   Actions: Fills the packet with random data, used for debugging ONLY.
*/

    /* Fill with random information */
    packet = "This is a test of the transmission function. -RMKW";

}
