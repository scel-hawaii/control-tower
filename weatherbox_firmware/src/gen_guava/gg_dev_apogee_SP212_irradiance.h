/*******************************
 *
 * File: gc_dev_apogee_sp212.h
 *
 * Contains prototypes for solar irradiance functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GG_APOGEE_SP212_IRRADIANCE_ A2

#ifndef GG_DEV_APOGEE_SP212_IRRADIANCE_H
#define GG_DEV_APOGEE_SP212_IRRADIANCE_H
void gg_dev_apogee_SP212_irradiance_open(void);
int gg_dev_apogee_SP212_irradiance_read(void);
#endif
