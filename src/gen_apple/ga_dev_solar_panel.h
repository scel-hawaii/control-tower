/*******************************
 *
 * File: ga_dev_solar_panel.h
 *
 * Contains prototypes for solar panel functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GA_SOLAR_PANEL_ A1

#ifndef GA_DEV_SOLAR_PANEL
#define GA_DEV_SOLAR_PANEL
void ga_dev_solar_panel_open(void);
int ga_dev_solar_panel_read(void);
#endif
