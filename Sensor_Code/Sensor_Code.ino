/*********************************************
 *
 *    File: Sensor_Code.ino
 *    REIS Weatherbox Firmware
 *
 *    Test .ino to check Sensor functions
 *
 ********************************************/

/* Program Libraries */
#include "config.h"
#include "sensors.h"

/* Arduino Libraries */
#include <Wire.h>
#include <SoftwareSerial.h>

/* External Libraries */
#include <SHT1x.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_MPL115A2.h>

/* Global Function Pointers */
void (*Sensors_init)(void);
int (*Sensors_sampleBatterymV)(void);
int (*Sensors_samplePanelmV)(void);
int (*Sensors_sampleSolarIrrmV)(void);
int (*Sensors_samplePressurepa)(void);
int (*Sensors_sampleHumiditypct)(void);
int (*Sensors_sampleTempdecic)(void);

/* Software Serial set up for debugging Cranberry and Dragonfruit */
SoftwareSerial mySerial(_PIN_RX, _PIN_TX);

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

    /* Generatiion Check */
    Gen_config();
    
    /* Initialize sensors */
    Sensors_init();

#ifdef APPLE
    Serial.begin(9600);
#elif defined(CRANBERRY) || defined(DRAGONFRUIT)
    mySerial.begin(9600);
#endif

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
    int BatterymV = -1;
    int SolarIrrmV = -1;
    int Humiditypct = -1;
    int PanelmV = -1;
    int Pressurepa = -1;
    int Tempdecic = -1;
    
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
#ifdef APPLE
    Serial.print("-------Sensor Data Readings-------\n");
    Serial.print("\nBatterymV Data:");
    Serial.println(BatterymV);

    Serial.print("\nSolarIrrmV Data:");
    Serial.println(SolarIrrmV);

    Serial.print("\nHumiditypct Data:");
    Serial.println(Humiditypct);

    Serial.print("\nPanelmV Data:");
    Serial.println(PanelmV);

    Serial.print("\nPressurepa Data:");
    Serial.println(Pressurepa);

    Serial.print("Tempdecic Data:");
    Serial.println(Tempdecic);

#elif defined(CRANBERRY) || defined(DRAGONFRUIT)
    mySerial.print("-------Sensor Data Readings-------\n");
    mySerial.print("\nBatterymV Data:");
    mySerial.println(BatterymV);

    mySerial.print("\nSolarIrrmV Data:");
    mySerial.println(SolarIrrmV);

    mySerial.print("\nHumiditypct Data:");
    mySerial.println(Humiditypct);

    mySerial.print("\nPanelmV Data:");
    mySerial.println(PanelmV);

    mySerial.print("\nPressurepa Data:");
    mySerial.println(Pressurepa);

    mySerial.print("Tempdecic Data:");
    mySerial.println(Tempdecic);
#endif
}
