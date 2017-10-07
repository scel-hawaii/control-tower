/*******************************
 *
 * File: gd_dev_solar_panel.h
 *
 * Contains prototypes for solar panel module functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GD_SOLAR_PANEL_ A0

#ifndef GD_DEV_SOLAR_PANEL
#define GD_DEV_SOLAR_PANEL
void gd_dev_solar_panel_open(void);
int gd_dev_solar_panel_read(void);
void gd_dev_solar_panel_test(void);
#endif
