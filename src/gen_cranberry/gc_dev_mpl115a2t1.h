#include <Arduino.h>

//#define _PIN_GC_MPL115A2T1_ AX

#ifndef GC_DEV_MPL115A2_H
#define GC_DEV_MPL115A2_H
void gc_dev_mpl115a2t1_open(void);
uint32_t gc_dev_mpl115a2t1_press_pa_read(void);
#endif
