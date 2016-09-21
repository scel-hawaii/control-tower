#include "gd_dev_sht1x.h"

#define _PIN_HUMID_CLK 7
#define _PIN_HUMID_DATA 8

static SHT1x sht1x(_PIN_HUMID_DATA, _PIN_HUMID_CLK);

void gd_dev_sht1x_open(void)
{

}

int gd_dev_sht1x_read(void)
{
    int value = 60;

    #ifndef SEN_STUB
    value =  sht1x.readHumidity();
    #endif

    return value;
}
