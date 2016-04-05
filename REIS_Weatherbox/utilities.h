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

// State of Health Macros
#define NORMAL 0
#define GOOD_SOLAR 1
#define POOR 2

struct P_STATE{
    int xbee;
    int sensor_array;
};

/* Struct to contain variables for lpf operations */
typedef struct lpf{
    float output;
    float alpha;
} LowPassFilter;

/* Struct definitions */
extern schema_health G_health; //GLOBAL!! Find alternative (pointers)
extern LowPassFilter G_solar_filter; //GLOBAL!! Find alternative (pointers)
extern LowPassFilter G_battery_filter; //GLOBAL!! Find alternative (pointers)

/* Global Timer Variable */
extern unsigned long G_health_transmit_timer;

/* Global XBee object */
extern XBee G_xbee;

//Number of samples to take
#define ADC_SAMPLE_NUM 30

/* Sets the good voltage threshold; Below this threshold, the box goes into
   a power saving mode and waits for the voltage to go above
   the THRESH_REINIT_SYSTEM (3.75 volts or approx. 45% capacity remaining)
   //Calculation: 3.730/5 * 1023 = 763.158 ~> 763 */
#define THRESH_GOOD_BATT_V 763

/* When the battery voltage is low, but still above ~30% and
   the solar power is good, the box transmits health data every 10 minutes
   //Calculation: (3.730/5)*1023 = 757.6338 ~> 757 */
#define THRESH_LOW_BATT_V 757

/* Solar is considered good it the solar panel voltage is ~6 volts
   //Calculation: (6/2)/5*1023 = 613.8 ~> 614 */
#define THRESH_GOOD_PANEL_V 614 

/* Solar is considered good if the solar irradiance voltage is ~2.5 volts
   //Calculation: (2.5/5)*1023 = 511.5 ~> 511 */
#define THRESH_GOOD_APOGEE_V 511

/* Defines the voltage where the system reinitializes transmission and sensing
   Check for the 3.830 volts (approx. 68% capacity remaining)
   //Calcuation: (3.830/5)*1023 = 783.618 ~> 783 */
#define THRESH_REINIT_SYSTEM 783

// Defines the alpha value for the battery lowpass filter
#define BATT_LOWPASS_ALPHA 0.005

//Defines the alpha value for the solar lowpass filter
#define BATT_LOWPASS_ALPHA 0.005

/* Overflow function */
int chk_overflow(unsigned long current_value, unsigned long previous_value);

/* Health functions */
long sampleBatteryVoltage(void);
void initHealthSamples(void);
int chkHealth(void);
void sendHealth(void);
void health_data_transmit(void);
void transmitPacketHealth(void);
void getPacketHealth(void);

/* Power Management functions */
void pstate_system(int state);
void pstate_xbee(int state, P_STATE *power_state);
void pstate_sensors_array(int state,P_STATE *power_state);
void sync_pstate(P_STATE power_state);

/* LPF functions */
void LPF_filter_init(LowPassFilter *f, float output, float alpha);
float LPF_update_filter(LowPassFilter *f, float new_value);
float LPF_get_current_output(LowPassFilter *f);
#endif
