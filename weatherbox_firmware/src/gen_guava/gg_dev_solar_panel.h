/*******************************
 *
 * File: gg_dev_solar_panel.h
 *
 * Contains prototypes for solar panel functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GG_SOLAR_PANEL_ A1

#ifndef GG_DEV_SOLAR_PANEL
#define GG_DEV_SOLAR_PANEL
void gg_dev_solar_panel_open(void);
int gg_dev_solar_panel_read(void);
#endif
