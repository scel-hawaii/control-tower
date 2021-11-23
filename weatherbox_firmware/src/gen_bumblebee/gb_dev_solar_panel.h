/*******************************
 *
 * File: gb_dev_solar_panel.h
 *
 * Contains prototypes for solar panel functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GB_SOLAR_PANEL_ A0

#ifndef GB_DEV_SOLAR_PANEL
#define GB_DEV_SOLAR_PANEL
void gb_dev_solar_panel_open(void);
int gb_dev_solar_panel_read(void);
#endif
