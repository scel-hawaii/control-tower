#include <Arduino.h>

#define _PIN_gg_BATT_ A3

#ifndef gg_DEV_BATT_H
#define gg_DEV_BATT_H
void gg_dev_batt_open(void);
int gg_dev_batt_read_raw(void);
int gg_dev_batt_read(void);
#endif
