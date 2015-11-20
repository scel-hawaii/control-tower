/*******************************************
 *
 *    File: low_pass.h
 *    REIS Weatherbox Firmware
 *
 *    Header file for low pass filter functions
 *
 ******************************************/

/* Check for previous includes */
#ifndef LOW_PASS_H
#define LOW_PASS_H

/* Struct to contain variables for lpf operations */
typedef struct lpf{
    float output;
    float alpha;
} LowPassFilter;

/* Define solar and battery filters as LPF type */
LowPassFilter solar_filter;
LowPassFilter battery_filter;

/* LPF functions */
void LPF_filter_init(LowPassFilter *f, float output, float alpha);
float LPF_update_filter(LowPassFilter *f, float new_value);
float LPF_get_current_output(LowPassFilter *f);

#endif
