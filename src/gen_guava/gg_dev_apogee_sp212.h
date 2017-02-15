#include <Arduino.h>

#define _PIN_gg_APOGEE_SP212_ A2

#ifndef gg_DEV_APOGEE_SP212_H
#define gg_DEV_APOGEE_SP212_H
void gg_dev_apogee_sp212_open(void);
int gg_dev_apogee_sp212_read_raw(void);
int gg_dev_apogee_sp212_read(void);
#endif
