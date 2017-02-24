/*******************************
 *
 * File: ga_dev_batt.h
 *
 * Contains prototypes for battery reading functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GA_BATT_ A3

#ifndef GA_DEV_BATT_H
#define GA_DEV_BATT_H
void ga_dev_batt_open(void);
int ga_dev_batt_read_raw(void);
int ga_dev_batt_read(void);
#endif
