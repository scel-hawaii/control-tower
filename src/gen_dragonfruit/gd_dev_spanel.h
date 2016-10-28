#include <Arduino.h>

#define _PIN_GD_SPANEL_ A6 

#ifndef GD_DEV_SPANEL
#define GD_DEV_SPANEL
void gd_dev_spanel_open(void);
int gd_dev_spanel_read(void);
#endif
