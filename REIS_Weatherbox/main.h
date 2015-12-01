/*******************************************
 *
 *    File: main.h
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
#ifndef MAIN_H
#define MAIN_H

/* Healthy Routine */
void Normal_Routine(int *count);

/* Unhealthy Routine */
void PowerSave_Routine(void);

#endif
