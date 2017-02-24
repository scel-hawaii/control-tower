/*******************************
 *
 * File: gg_dev_sht1x.h
 *
 * Contains prototypes for solar panel functions
 *
 ******************************/

#include <Arduino.h>
#include <SHT1x.h>

#ifndef gg_DEV_SHT1X_H
#define gg_DEV_SHT1X_H
void gg_dev_sht1x_open(void);
int gg_dev_sht1x_avail(void);
int gg_dev_sht1x_read(void);
#endif
