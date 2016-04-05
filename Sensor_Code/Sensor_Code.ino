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
#include <Adafruit_ADS1015.h>
#include <HIH613x.h>

/* Global Function Pointers */
void (*Sensors_init)(void);
long (*Sensors_sampleBatterymV)(void);
long (*Sensors_samplePanelmV)(void);
long (*Sensors_sampleSolarIrrmV)(void);
long (*Sensors_samplePressurepa)(void);
long (*Sensors_sampleHumiditypct)(void);
long (*Sensors_sampleTempdecic)(void);

/* Software Serial set up for debugging Cranberry and Dragonfruit */
#if defined(CRANBERRY) || defined(DRAGONFRUIT)
SoftwareSerial mySerial(_PIN_RX, _PIN_TX);
#endif

/* Iterator to keep track of test count */
int G_i;

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
    G_i = 0;
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
    long BatterymV = -1;
    long SolarIrrmV = -1;
    long Humiditypct = -1;
    long PanelmV = -1;
    long Pressurepa = -1;
    long Tempdecic = -1;
    long RoofTempdecic = -1;

    /* Increment */
    G_i++;
    
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
#ifdef APPLE
    RoofTempdecic = a_Sensors_sampleRoofTempdecic();
    delay(1000);
#endif

    /* Debug: Print the values to the Arduino Serial Monitor */
#ifdef APPLE
    Serial.print("-------Sensor Data Readings #");
    Serial.print(G_i);
    Serial.print("-------");
    
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

    Serial.print("\nTempdecic Data:");
    Serial.println(Tempdecic);
    
    Serial.print("\nRoofTempdecic Data:");
    Serial.println(RoofTempdecic);

#elif defined(CRANBERRY) || defined(DRAGONFRUIT)
    mySerial.print("-------Sensor Data Readings #");
    mySerial.print(G_i);
    mySerial.print("-------");
    
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

    mySerial.print("\nTempdecic Data:");
    mySerial.println(Tempdecic);
    mySerial.print("\n");
#endif
}
