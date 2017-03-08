/*******************************
 *
 * File: gc_dev_solar_panel.h
 *
 * Contains prototypes for solar panel functions
 *
 ******************************/

#include <Adafruit_ADS1015.h>
#include <Wire.h>

#ifndef GC_DEV_SOLAR_PANEL
#define GC_DEV_SOLAR_PANEL
void gc_dev_solar_panel_open(void);
uint16_t gc_dev_solar_panel_read(void);
void gc_dev_solar_panel_test(void);
#endif
