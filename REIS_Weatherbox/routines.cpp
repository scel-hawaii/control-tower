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
 *    Name:        Normal_RoutineUART
 *    Returns:     Nothing
 *    Parameter:   int *count
 *    Description: Routine that runs with the battery
 *                     voltage level is good. Uses 
 *                     UART transmission.
 *
 ******************************************/
void Normal_RoutineUART(int *count){

    /* Variable Initialization */
    long wait_ms = 1000;                     //Used to ensure we poll 
                                             //    exactly every second
    unsigned long transmit_timer = millis(); // Initialize timer

    /* Poll sensors & construct packet */
    Packet_Con();

    /* Increment the poll counter */
    (*count)++;

    /* Transmit after 3 polls (~3 Seconds) (UART) */
    if((*count) >= 3){
        Packet_Transmit();
        Packet_Clear();
        (*count) = 0;
    }

    /* Wait to ensure we poll exactly every second */
    while((millis() - transmit_timer) <= wait_ms);
}

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

    /* Initialize Variable */
    unsigned long health_transmit_timer = 0;
    unsigned long transmit_timer = 0;
    int delay = 0;

    /* Change Power State */
    pstate_system(_POWER_SAVE);

    /* Update Battery Voltage in LPF filter */
    //!!!battery_filter!!!
    LPF_update_filter(&G_battery_filter, analogRead(_PIN_BATT_V));

    /* Initialize time since the last transmission */
    health_transmit_timer = millis();

    /* Constantly check battery voltage */
    //!!!battery_filter!!!
    while(LPF_get_current_output(&G_battery_filter) < THRESH_REINIT_SYSTEM)
    {
        /* Send health data */
        sendHealth();

        /* Initialize timer */
        transmit_timer = millis();

        /* Set Dealy amount */
        delay = 200;

        /* Delay */
        while((millis() - transmit_timer) <= delay);

        /* Update Filter */
        //!!!battery_filter!!!
        LPF_update_filter(&G_battery_filter, analogRead(_PIN_BATT_V));
    }

    /* Loop condition met, Battery health is good again */
    pstate_system(_ACTIVE);

    /* Delay to ensure all components activate */
    transmit_timer = millis();
    delay = 3000;
    while((millis() - transmit_timer) <= delay);

    /* Update Battery and Solar filters */
    //!!!battery_filter!!!
    LPF_filter_init(&G_battery_filter, G_battery_filter.output, BATT_LOWPASS_ALPHA);
    LPF_filter_init(&G_solar_filter, G_solar_filter.output, BATT_LOWPASS_ALPHA);
}
