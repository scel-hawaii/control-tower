/*******************************
 *
 * File: gd_dev_adafruit_MPL115A2_pressure.cpp
 *
 * This module is a driver for the MPL115A2 pressure sensor
 * that measures pressure in Pa. Technically this is not an
 * Adafruit sensor - Adafruit creates the breakout board for
 * this sensor that is actually manufactured by Freescale.
 *
 * Product page: http://www.nxp.com/products/sensors/pressure-sensors/barometric-pressure-15-to-115-kpa/50-to-115kpa-absolute-digital-pressure-sensor:MPL115A
 * Datasheet: http://www.nxp.com/assets/documents/data/en/data-sheets/MPL115A2.pdf
 *
 ******************************/

#include "gd_dev_adafruit_MPL115A2_pressure.h"
#include "Adafruit_MPL115A2.h"

static Adafruit_MPL115A2 mpl115a2;

/******************************
 *
 * Name:        gd_dev_adafruit_MPL115A2_pressure_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize pressure sensor
 *
 ******************************/

void gd_dev_adafruit_MPL115A2_pressure_open(void){
    mpl115a2.begin();
}

/******************************
 *
 * Name:        gd_dev_adafruit_MPL115A2_pressure_pa_read
 * Returns:     Pressure value in Pa
 * Parameter:   Nothing
 * Description: Reads pressure sensor
 *
 ******************************/

uint32_t gd_dev_adafruit_MPL115A2_pressure_pa_read(void){
    uint32_t value = 100000;

    #ifndef SEN_STUB
    value = mpl115a2.getPressure() * 1000;
    #endif

    return value;
}

/******************************
 *
 * Name:        gd_dev_adafruit_MPL115A2_pressure_pa_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the
 *              sensor and displays the sample to Serial Monitor
 *
 ******************************/

void gd_dev_adafruit_MPL115A2_pressure_pa_test(void){
    Serial.println(F("[P] Check mpl115a2t1_pressure_pa value"));
    uint32_t mpl115a2t1_pressure_pa_val = gd_dev_adafruit_MPL115A2_pressure_pa_read();

    Serial.print(F("[P] mpl115a2t1_pressure_pa value: "));
    Serial.print(mpl115a2t1_pressure_pa_val);
    Serial.println(F(" Pa"));

    if(mpl115a2t1_pressure_pa_val < 0){
        Serial.println(F("[P] \tError: mpl115a2t1 pressure out of range"));
    }
}
