/*****************************************
 *
 *    File: utilities.h
 *    REIS Weatherbox Firmware
 *    Header file for utility functions
 *
 *****************************************/

/* Program Libraries */
#include "schema.h"
#include "config.h"

/* External Libraries */
#include <EEPROM.h>
#include <XBee.h>

/* Check for previous includes */
#ifndef UTILITIES_H
#define UTILITIES_H

#define TRUE 1
#define FALSE 0

//Power Management Macros
#define _ON 1
#define _OFF 0
#define _ACTIVE 1
#define _POWER_SAVE 0

struct P_STATE{
    int xbee;
    int sensor_array;
};

/* Struct to contain variables for lpf operations */
typedef struct lpf{
    float output;
    float alpha;
} LowPassFilter;

/* Global XBee object */
extern XBee G_xbee;

//Number of samples to take
#define ADC_SAMPLE_NUM 30

/* Overflow function */
int chk_overflow(unsigned long current_value, unsigned long previous_value);

/* Power Management functions */
void pstate_system(int state);
void pstate_xbee(int state, P_STATE *power_state);
void pstate_sensors_array(int state,P_STATE *power_state);
void sync_pstate(P_STATE power_state);

#endif
