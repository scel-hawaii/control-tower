/*******************************
 *
 * File: gd_dev_apogee_sp215.h 
 *
 * Contains prototypes for solar irradiance functions
 *
 ******************************/

#include <Arduino.h>
#include <Wire.h>

#define _DEV_ADDR_GD_ADS1100_ 0x48

#ifndef GD_DEV_APOGEE_SP215_H
#define GD_DEV_APOGEE_SP215_H
void gd_dev_apogee_sp215_open(void);
uint32_t gd_dev_apogee_sp215_read(void);
#endif
