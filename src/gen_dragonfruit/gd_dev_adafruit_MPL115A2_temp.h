/*******************************
 *
 * File: gd_dev_adafruit_MPL115A2_temp.h 
 *
 * Contains prototypes for temperature functions
 *
 ******************************/

#include "Adafruit_MPL115A2.h"

#ifndef _GD_ADAFRUIT_MPL115A2_TEMP_H
#define _GD_ADAFRUIT_MPL115A2_TEMP_H
void gd_dev_adafruit_MPL115A2_temp_open(void);
uint16_t gd_dev_adafruit_MPL115A2_temp_read(void);
#endif
