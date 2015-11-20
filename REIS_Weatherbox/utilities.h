/*****************************************
 *
 *    File: utilities.h
 *    REIS Weatherbox Firmware
 *    Header file for utility functions
 *
 *****************************************/

#include "low_pass.h"
#include "sensors.h"

#define TRUE 1
#define FALSE 0
#define ADC_SAMPLE_NUM 200
#define THRESH_GOOD_BATT_V 763
#define THRESH_GOOD_APOGEE_V 511
#define THRESH_GOOD_PANEL_V 614 

/* State of Health macros */
#define NORMAL 0
#define GOOD_SOLAR 1
#define POOR 2

int chk_overflow(unsigned long current_value, unsigned long previous_value);
long sampleBatteryVoltage(void);
void configureADC(void);
