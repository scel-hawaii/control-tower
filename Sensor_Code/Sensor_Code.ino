/*********************************************
 *
 *    File: Sensor_Code.ino
 *    REIS Weatherbox Firmware
 *
 *    Test .ino to check Sensor functions
 *
 ********************************************/

/* Program Libraries */
#include "apple.h"
#include "sensors.h"

/* Arduino Libraries */
#include <Wire.h>

/* External Libraries */
#include <SHT1x.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <Adafruit_BMP085.h>

/*******************************************
 *
 *    Name:        setup 
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Runs once at the start of the sequence.
 *                     Used for initialization. Place all
 *                     init scripts here.
 *
 ******************************************/
void setup(){

    /* Initialize sensors */
    Sensors_init();
    Serial.begin(9600);
}

/*******************************************
 *
 *    Name:        loop 
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Main program function runs constantly.
 *                     Executed after setup(). and will
 *                     continue running indefinitely,
 *                     unless conditions stop it.
 *
 ******************************************/
void loop(){

    /* Variable Declarations */
    int BatterymV;
    int SolarIrrmV;
    int Humiditypct;
    int PanelmV;
    int Pressurepa;
    int Tempdecic;
    
    /* Poll each sensor and delay for 1 second after each poll */
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

    /* Debug: Print the values to the Arduino Serial Monitor */
    Serial.print("Sample Data:\n");
    Serial.println(BatterymV);
    Serial.println(SolarIrrmV);
    Serial.println(Humiditypct);
    Serial.println(PanelmV);
    Serial.println(Pressurepa);
    Serial.println(Tempdecic);

}
