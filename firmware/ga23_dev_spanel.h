#include <Arduino.h>

#define _PIN_GA23_SPANEL_ A1

#ifndef GA23_DEV_SPANEL
#define GA23_DEV_SPANEL
void ga23_dev_spanel_open(void);
int ga23_dev_spanel_read(void);
#endif

