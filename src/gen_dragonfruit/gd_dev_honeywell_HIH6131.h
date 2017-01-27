/*******************************
 *
 * File: gd_dev_honeywell_HIH6131.h 
 *
 * Contains prototypes for humidty sensor functions
 *
 ******************************/

#include "HIH613x.h"

#define _PIN_GD_HONEYWELL_HIH6131_ 0x27

#ifndef _GD_HONEYWELL_HIH6131_H
#define _GD_HONEYWELL_HIH6131_H

void gd_dev_honeywell_HIH6131_open(void);
int gd_dev_honeywell_HIH6131_read(void);
#endif
