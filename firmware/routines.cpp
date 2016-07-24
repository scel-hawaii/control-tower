/*******************************************
 *
 *    File: routines.cpp
 *    REIS Weatherbox Firmware
 *
 *    File contains the routines in which the
 *        weatherbox may operate in.
 *
 ******************************************/

/* Program Libraries */
#include "routines.h"


/*******************************************
 *
 *    Name:        Normal_RoutineBIN
 *    Returns:     Nothing
 *    Parameter:   int *count
 *    Description: Routine that runs with the battery
 *                     voltage level is good. Uses
 *                     Binary transmission.
 *
 ******************************************/
void Normal_RoutineBIN(int *count){
    print_log("Routine count: ");

    char buf[12]; // "-2147483648\0"
    print_log(itoa((*count), buf, 10));

    /* Variable Initialization */
    long wait_ms = 1000;                     //Used to ensure we poll 
                                             //    exactly every second
    unsigned long transmit_timer = millis(); // Initialize timer

    /* Poll sensors & construct packet */
    Packet_Con();

    /* Increment the poll counter */
    (*count)++;

    /* Transmit after 60 polls (~60 Seconds) (BINARY) */
    if((*count) >= 60){
        print_log("Transmitting.");
        Packet_Transmit();
        Packet_Clear();
        (*count) = 0;
    }

    /* Wait to ensure we poll exactly every second */
    while((millis() - transmit_timer) <= wait_ms);
}
