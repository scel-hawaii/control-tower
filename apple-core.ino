/*
 * Apple Core
 *
 */

/* Include program libs */
#include "apple.h"
#include "sensors.h"

/* Include arduino libs */
#include <Wire.h>

/* Include external libs */
#include <SHT1x.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <Adafruit_BMP085.h>

void setup(){
    Sensors_init();
    Serial.begin(9600);
}

void loop(){



}
