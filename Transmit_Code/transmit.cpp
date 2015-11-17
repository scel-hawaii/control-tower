/*******************************************
 *
 *    File: transmit.cpp
 *    REIS Weatherbox Firmware
 *
 *    File containing Transmission functions
 *
 ******************************************/

/* Program Libraries */
#include "transmit.h"

/******************************************
 *
 *   Name:        Packet_ClearUART
 *   Returns:     Nothing
 *   Parameter:   uint8_t *packet
 *   Description: Clears/Initializes the packet to
 *                    NULL.
 *
 *****************************************/
void Packet_ClearUART(uint8_t *packet){

    /* Variables Declarations */
    int i = 0;

    /* Set packet to NULL */
    for(i = 0; i < MAX_SIZE; i++){
        packet[i] = '\0';
    }
}


/******************************************
 *
 *   Name:        Packet_ClearBIN
 *   Returns:     Nothing
 *   Parameter:   schema_3 *packet
 *   Description: Clears/Initializes the packet schema
 *                    information.
 *
 *****************************************/
void Packet_ClearBIN(schema_3 *packet){

    /* Variables used for indexes */
    int i = 0;

    /* Initialize values contained in the packet */
    packet.schema = 3;
    packet.address = EEPROM.read(2) | (EEPROM.read(3) << 8); //Addr from EEPROM
    packet.uptime_ms = 0;
    packet.n = 0;
    packet.bm085_press_pa = 0;
    packet.bmp085_temp_decic = 0;
    packet.humidity_ceenti_pct = 0;
    
    /* Use a for loop to clear the info for the data with multiple points */
    for(i = 0; i < 60; i++){ //Simulates one minute
        
	/* Polled every 10 seconds */
	packet.batt_mv[i/10] = 0;
	packet.panel_mv[i/10] = 0;

	/* Polled every 3 seconds */
	packet.apogee_w_m2[i/3] = 0;
    }
}

/******************************************
 *
 *   Name:        Packet_ConUART
 *   Returns:     Nothing
 *   Parameter:   uint8_t *packet
 *   Description: Constructs a packet with data polled 
 *                    from the sensors.
 *
 *****************************************/
void Packet_ConUART(uint8_t *packet){

    /* EMPTY */
}

/******************************************
 *
 *   Name:        Packet_ConBIN
 *   Returns:     Nothing
 *   Parameter:   schema_3 *packet
 *   Description: Constructs a packet with data polled
 *                    from the sensors.
 *
 *****************************************/
void Packet_ConBIN(schema_3 *packet){

    /* EMPTY */
}

/******************************************
 *
 *   Name:        Packet_TransmitUART
 *   Returns:     Nothing
 *   Parameter:   uint8_t *packet
 *   Description: Transmits using Arduino Xbee functions,
 *                    Xbees must be in API mode.
 *
 *****************************************/
void Packet_TransmitUART(uint8_t *packet){

    /* Variable Declarations */
    XBee xbee = XBee();    //Create Xbee Object
    int length = 0;        //Length of the packet to be sent
    int i = 0;             //Variable to be used to iterate across the packet

    /* Obtain address of receiving end */
    XBeeAddress64 addr64 = XBeeAddress64(0,0); //!!TEST if this gets right addr

    /* Get length of packet */
    length = strlen((char *) packet);

#ifdef DEBUG_S
    /* Debug */
    Serial.print("\nLength is: ");
    Serial.print(length);
#endif

    /* Transfer the packet */
    ZBTxRequest zbTx = ZBTxRequest(addr64, packet, length);
    xbee.send(zbTx);
}

/******************************************
 *
 *   Name:        Packet_TransmitBIN
 *   Returns:     Nothing
 *   Parameter:   schema_3 *packet
 *   Description: Transmits using Arduino Xbee functions,
 *                    the packet is transfered as a
 *                    binary packet.
 *
 *****************************************/
void Packet_TransmitBIN(schema_3 *packet){

    /* Packet to be transmitted */
    uint8_t payload[MAX_SIZE];

    /* Clear the payload */
    memset(payload, '\0', sizeof(payload));

    /* Obtain length of the packet */
    length = strlen((char *) packet);

#ifdef DEBUG_S
    /* Debug */
    Serial.print("\nLength is: ");
    Serial.print(length);
#endif

    /* Transfer information into payload */
    memcpy(payload, &packet, length);
    
    /* Transfer the payload */
    ZBTxRequest zbTx = ZBTxRequest(addr64, payload, length);
    xbee.send(zbTx);
}

/******************************************
 *
 *   Name:        Test_Packet_GenUART
 *   Returns:     Nothing
 *   Parameter:   uint8_t *packet
 *   Description: Constructs a packet with hard-coded
 *                    information.  Used for the initial
 *                    test of the Transmission functions.
 *                    To be replaced by Packet Construction.
 *
 *****************************************/
void Test_Packet_GenUART(uint8_t *packet){

    /* Necessary Variables */
    int i = 0;

    /* Set up array */
    String s;
    
    /* Fill with Hard-coded information */
    s = "test yes";
    s += '\0';

    /* Put array information into Packet */
    for(i = 0; i < s.length(); i++){
      packet[i] = s[i];
    }
}

/******************************************
 *
 *   Name:        Test_Packet_GenBIN
 *   Returns:     Nothing
 *   Parameter:   schema_3 *packet
 *   Description: Constructs a packet with hard-coded
 *                    information.  Used for the initial
 *                    test of the Transmission functions.
 *                    To be replaced by Packet Construction.
 *
 *****************************************/
void Test_Packet_GenBIN(schema_3 *packet){

    /* Hard-coded data to put into packet */
    int batt_mv_raw = 1;
    int panel_mv_raw = 2;
    int apogee_raw = 3;
    int pressure_raw = 4;
    int temperaure_raw = 5;
    int humidity_raw = 6;
    int n = 10;
    unsigned long uptime = 1000;

    /* Store values into packet */
    packet.batt_mv[n/10] = batt_mv_raw;
    packet.panel_mv[n/10] = panel_mv_raw;
    packet.apogee_w_m2[n/3] = apogee_raw;
    packet.bmp085_press_pa = pressure_raw;
    packet.bmp085_temp_decic = temperature_raw;
    packet.humidity_centi_pct = humidity_raw;
    packet.n = n;
    packet.uptime_ms = uptime;
}
