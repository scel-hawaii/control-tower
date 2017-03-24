/*******************************
 *
 * File: ga_dev_sht1x.h
 *
 * Contains prototypes for SHT1x sensor functions
 *
 ******************************/

#include <Arduino.h>
#include <SHT1x.h>

#ifndef GA_DEV_SENSIRION_SHT1X_HUMIDITY_H
#define GA_DEV_SENSIRION_SHT1X_HUMIDITY_H
void ga_dev_sensirion_SHT1X_humidity_open(void);
int ga_dev_sensirion_SHT1X_humidity_read(void);
#endif
