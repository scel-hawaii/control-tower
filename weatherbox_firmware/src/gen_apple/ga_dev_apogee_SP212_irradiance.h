/*******************************
 *
 * File: ga_dev_apogee_sp212.h
 *
 * Contains prototypes for solar irradiance functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GA_APOGEE_SP212_IRRADIANCE_ A2

#ifndef GA_DEV_APOGEE_SP212_IRRADIANCE_H
#define GA_DEV_APOGEE_SP212_IRRADIANCE_H
void ga_dev_apogee_SP212_irradiance_open(void);
int ga_dev_apogee_SP212_irradiance_read_raw(void);
int ga_dev_apogee_SP212_irradiance_read(void);
#endif
