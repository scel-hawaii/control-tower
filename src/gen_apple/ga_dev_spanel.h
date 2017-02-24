/*******************************
 *
 * File: ga_dev_spanel.h 
 *
 * Contains prototypes for solar panel functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GA_SPANEL_ A1

#ifndef GA_DEV_SPANEL
#define GA_DEV_SPANEL
void ga_dev_spanel_open(void);
int ga_dev_spanel_read(void);
#endif
