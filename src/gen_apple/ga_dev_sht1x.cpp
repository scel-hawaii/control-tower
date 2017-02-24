/*******************************
 *
 * File: ga_dev_sht1x.cpp
 *
 * This module is a driver for the SHT1x sensor. This
 * sensor measures humidity in percentage.
 *
 * Product page:
 *
 ******************************/

#include "ga_dev_sht1x.h"

#define _PIN_HUMID_CLK 7
#define _PIN_HUMID_DATA 8

static SHT1x sht1x(_PIN_HUMID_DATA, _PIN_HUMID_CLK);

/******************************
 *
 * Name:        ga_dev_sht1x_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Nothing (Used for consistency)
 *
 ******************************/

void ga_dev_sht1x_open(void)
{

}

/******************************
 *
 * Name:        ga_dev_sht1x_read
 * Returns:     Value of humidity in percentage
 * Parameter:   Nothing
 * Description: Samples the SHT1x to get humidity value
 *
 ******************************/

int ga_dev_sht1x_read(void)
{
    int value = 60;

    #ifndef SEN_STUB
    value =  sht1x.readHumidity();
    #endif

    return value;
}
