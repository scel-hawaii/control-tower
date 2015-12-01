/*******************************************
 *
 *    File: main.cpp
 *    REIS Weatherbox Firmware
 *
 *    File contains the routines in which the
 *        weatherbox may operate in.
 *
 ******************************************/

/* Program Libraries */
#include "main.h"

/*******************************************
 *
 *    Name:        Normal_Routine
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Routine that runs with the battery
 *                     voltage level is good.
 *
 ******************************************/
void Normal_Routine(int *count){

    /* Variable Initialization */
    long wait_ms = 1000;  //Used to ensure we poll exactly every second

    /* Poll sensors & construct packet */
    Packet_Con();

    /* Increment the poll counter */
    (*count)++;

    /* Transmit after 60 polls (BINARY) */
    if((*count) >= 60){
        Packet_Transmit();
        Packet_Clear();
	(*count) = 0;
    }

    /* Wait to ensure we poll exactly every second */
    while((millis() - transmit_timer) <= wait_ms);

}

/*******************************************
 *
 *    Name:        PowerSave_Routine
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Routine that runs when the battery
 *                     voltage level is bad.  It will
 *                     stop polling the sensors and
 *                     check the battery voltage until
 *                     it returns to a good level.  It
 *                     will send weatherbox health data
 *                     instead of sending the data polled
 *                     from sensors in this state.
 *
 ******************************************/
void PowerSave_Routine(void){

}
