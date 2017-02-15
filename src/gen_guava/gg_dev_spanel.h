#include <Arduino.h>

#define _PIN_gg_SPANEL_ A1

#ifndef gg_DEV_SPANEL
#define gg_DEV_SPANEL
void gg_dev_spanel_open(void);
int gg_dev_spanel_read(void);
#endif
