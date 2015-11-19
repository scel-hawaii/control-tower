/*****************************************
 *
 *    File: utilities.h
 *    REIS Weatherbox Firmware
 *    Header file for utility functions
 *
*****************************************/

#include "sensors.h"

#define TRUE 1
#define FALSE 0
#define ADC_SAMPLE_NUM 200

int chk_overflow(unsigned long current_value, unsigned long previous_value);
long sampleBatteryVoltage(void);
void configureADC(void);
