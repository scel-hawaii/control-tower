#include <Arduino.h>

#define _PIN_GC_APOGEE_SP212_ A2

#ifndef GC_DEV_APOGEE_SP212_H
#define GC_DEV_APOGEE_SP212_H
void gc_dev_apogee_sp212_open(void);
int gc_dev_apogee_sp212_read_raw(void);
int gc_dev_apogee_sp212_read(void);
#endif
