#include <Arduino.h>

#define _PIN_GD_APOGEE_SP212_ A2

#ifndef GD_DEV_APOGEE_SP212_H
#define GD_DEV_APOGEE_SP212_H
void gd_dev_apogee_sp212_open(void);
int gd_dev_apogee_sp212_read(void);
#endif
