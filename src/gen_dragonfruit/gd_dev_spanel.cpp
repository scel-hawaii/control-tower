#include "gd_dev_spanel.h"

void gd_dev_spanel_open(void){
    pinMode(_PIN_GD_SPANEL_, INPUT);
}

int gd_dev_spanel_read(void){
    float value = 555.0;
    #ifndef SEN_STUB

    /* The solar panel has a maximum output voltage of 6V but the ATmega328P
    microcontroller only allows a maximum input voltage of 5V. To prevent a
    saturated signal reading, A physical voltage divider is implemented on the
    board. To account for this voltage divider, a scaling factor of 2 is used. */
    value = 2.0 * (float)analogRead(_PIN_GD_SPANEL_) *(5000.0/1023);
    #endif
    return value;
}
