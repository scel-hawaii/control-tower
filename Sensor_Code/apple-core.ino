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
    int BatterymV;
    int SolarIrrmV;
    int Humiditypct;
    int PanelmV;
    int Pressurepa;
    int Tempdecic;
    
    BatterymV = Sensors_sampleBatterymV();
    delay(1000);
    SolarIrrmV = Sensors_sampleSolarIrrmV();
    delay(1000);
    Humiditypct = Sensors_sampleHumiditypct();
    delay(1000);
    PanelmV = Sensors_samplePanelmV();
    delay(1000);
    Tempdecic = Sensors_sampleTempdecic();
    delay(1000);
    Pressurepa = Sensors_samplePressurepa();
    delay(1000);

    Serial.print("Sample Data:\n");
    Serial.println(BatterymV);
    Serial.println(SolarIrrmV);
    Serial.println(Humiditypct);
    Serial.println(PanelmV);
    Serial.println(Pressurepa);
    Serial.println(Tempdecic);

}
