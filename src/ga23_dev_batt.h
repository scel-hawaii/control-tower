#include <Arduino.h>

#define _PIN_GA23_BATT_ A3

#ifndef GA23_DEV_BATT_H
#define GA23_DEV_BATT_H
void ga23_dev_batt_open(void);
int ga23_dev_batt_read(void);
#endif

