/*******************************************
 *
 *    File: routines.h
 *    REIS Weatherbox Firmware
 *
 *    Main file to contain the routines in
 *        which to operate in for the 
 *        weatherbox.
 *
 ******************************************/

/* Program Libraries */
#include "transmit.h"
#include "utilities.h"

/* Check for previous includes */
#ifndef ROUTINES_H
#define ROUTINES_H

/* Healthy Routine */
void Normal_RoutineUART(int *count);
void Normal_RoutineBIN(int *count);

/* Unhealthy Routine */
void PowerSave_Routine(void);

#endif
