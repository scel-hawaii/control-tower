/*******************************
 *
 * File: gd_dev_spanel.h 
 *
 * Contains prototypes for solar panel module functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GD_SPANEL_ A0

#ifndef GD_DEV_SPANEL
#define GD_DEV_SPANEL
void gd_dev_spanel_open(void);
int gd_dev_spanel_read(void);
#endif
