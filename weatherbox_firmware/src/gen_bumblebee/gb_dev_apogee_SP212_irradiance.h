/*******************************
 *
 * File: gb_dev_apogee_sp212.h
 *
 * Contains prototypes for solar irradiance functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GB_APOGEE_SP212_IRRADIANCE_ A1

#ifndef GB_DEV_APOGEE_SP212_IRRADIANCE_H
#define GB_DEV_APOGEE_SP212_IRRADIANCE_H
void gb_dev_apogee_SP212_irradiance_open(void);
int gb_dev_apogee_SP212_irradiance_read_raw(void);
int gb_dev_apogee_SP212_irradiance_read(void);
#endif
