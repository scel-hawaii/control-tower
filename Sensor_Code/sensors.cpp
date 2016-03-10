/*******************************************
 *
 *    File: sensors.cpp 
 *    REIS Weatherbox Firmware
 *
 *    File containing Sensor Functions
 *
 ******************************************/

/* Program Libraries */
#include "sensors.h"
#include "config.h"

/* Set Pins */
#ifdef APPLE
OneWire oneWire1(_PIN_AMB_TEMP);
DallasTemperature dallas_amb_sen(&oneWire1);
OneWire oneWire2(_PIN_ROOF_TEMP);
DallasTemperature dallas_roof_sen(&oneWire2);

SHT1x sht1x(_PIN_HUMID_DATA, _PIN_HUMID_CLK);

Adafruit_BMP085 bmp085;
Adafruit_INA219 ina219_Solar;

#elif defined(CRANBERRY)
Adafruit_MPL115A2 mpl115a2;
Adafruit_ADS1115 PyroADC_C(_ADDR_PYRO);
HIH613x hih6131(_ADDR_HYGRO);

#elif defined(DRAGONFRUIT)
Adafruit_MPL115A2 mpl115a2;
MCP342X PyroADC_D;
HIH613x hih6131(_ADDR_HYGRO);
#endif

/*---------------------------*/
/*---------- Apple ----------*/
/*---------------------------*/

/*******************************************
 *
 *    Name:        a_Sensors_init      
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Intializes  sensors using various 
 *                     Arduino libraries.
 *
 ******************************************/
void a_Sensors_init(void){
    bmp085.begin();
    ina219_Solar.begin();
}

/*******************************************
 *
 *    Name:        a_Sensors_sampleBatterymV     
 *    Returns:     Battery Voltage (mV)
 *    Parameter:   Nothing
 *    Description: Checks the battery voltage.
 *
 ******************************************/
long a_Sensors_sampleBatterymV(void){
    long value = analogRead(_PIN_BATT_V)*5000.0/1023;
    return value;
}

/*******************************************
 *
 *    Name:        a_Sensors_samplePanelmV 
 *    Returns:     Panel Voltage (mV)
 *    Parameter:   Nothing
 *    Description: Checks the Solar Panel voltage.
 *
 ******************************************/
long a_Sensors_samplePanelmV(void){
    long value = 2*analogRead(_PIN_SOLAR_V)*5000.0/1023;
    return value;
}

/*******************************************
 *
 *    Name:        a_Sensors_sampleSolarIrrmV 
 *    Returns:     Solar Irradiance Voltage (mV)
 *    Parameter:   Nothing
 *    Description: Checks the Solar Irradiance level.
 *
 ******************************************/
long a_Sensors_sampleSolarIrrmV(void){
    long value = analogRead(_PIN_APOGEE_V)*5000.0/1023;
    return value;
}

/*******************************************
 *
 *    Name:        a_Sensors_samplePressurepa 
 *    Returns:     Weather Pressure (pa)
 *    Parameter:   Nothing
 *    Description: Checks the current Pressure.
 *
 ******************************************/
long a_Sensors_samplePressurepa(void){
    long value = bmp085.readPressure();
    return value;
}

/*******************************************
 *
 *    Name:        a_Sensors_Humiditypct 
 *    Returns:     Humidity (pct)
 *    Parameter:   Nothing
 *    Description: Checks the current Humidity.
 *
 ******************************************/
long a_Sensors_sampleHumiditypct(void){
    long value =  sht1x.readHumidity();
    return value;
}

/*******************************************
 *
 *    Name:        a_Sensors_sampleTempdecic 
 *    Returns:     Temperature (Degrees C)
 *    Parameter:   Nothing
 *    Description: Checks the current Temperature.
 *
 ******************************************/
long a_Sensors_sampleTempdecic(void){
    long value =  bmp085.readTemperature()*10;
    return value;
}

/*---------------------------*/
/*-------- Cranberry --------*/
/*---------------------------*/

/*******************************************
 *
 *    Name:        c_Sensors_init      
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Intializes  sensors using various 
 *                     Arduino libraries.
 *
 ******************************************/
void c_Sensors_init(void){
	mpl115a2.begin();
}

/*******************************************
 *
 *    Name:        c_Sensors_sampleBatterymV     
 *    Returns:     Battery Voltage (mV)
 *    Parameter:   Nothing
 *    Description: Checks the battery voltage.
 *
 ******************************************/
long c_Sensors_sampleBatterymV(void){
	return -1;
}

/*******************************************
 *
 *    Name:        c_Sensors_samplePanelmV 
 *    Returns:     Panel Voltage (mV)
 *    Parameter:   Nothing
 *    Description: Checks the Solar Panel voltage.
 *
 ******************************************/
long c_Sensors_samplePanelmV(void){
	return -1;
}

/*******************************************
 *
 *    Name:        c_Sensors_sampleSolarIrrmV 
 *    Returns:     Solar Irradiance Voltage (mV)
 *    Parameter:   Nothing
 *    Description: Checks the Solar Irradiance level.
 *
 ******************************************/
long c_Sensors_sampleSolarIrrmV(void){
	long value = 0;
	value = PyroADC_C.readADC_SingleEnded(0);
	return value;
}

/*******************************************
 *
 *    Name:        c_Sensors_samplePressurepa 
 *    Returns:     Weather Pressure (pa)
 *    Parameter:   Nothing
 *    Description: Checks the current Pressure.
 *
 ******************************************/
long c_Sensors_samplePressurepa(void){
	long value = 0;
	value = mpl115a2.getPressure()*1000;
	return value;
}

/*******************************************
 *
 *    Name:        c_Sensors_Humiditypct 
 *    Returns:     Humidity (pct)
 *    Parameter:   Nothing
 *    Description: Checks the current Humidity.
 *
 ******************************************/
long c_Sensors_sampleHumiditypct(void){
	long value = 0;
	hih6131.update();
	value = hih6131.getHumidity();
	return value;
}

/*******************************************
 *
 *    Name:        c_Sensors_sampleTempdecic 
 *    Returns:     Temperature (Degrees C)
 *    Parameter:   Nothing
 *    Description: Checks the current Temperature.
 *
 ******************************************/
long c_Sensors_sampleTempdecic(void){
	long value = 0;
	value = mpl115a2.getTemperature()*10;
	return value;
}
/*---------------------------*/
/*------- Dragonfruit -------*/
/*---------------------------*/

/*******************************************
 *
 *    Name:        d_Sensors_init      
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Intializes  sensors using various 
 *                     Arduino libraries.
 *
 ******************************************/
void d_Sensors_init(void){
	Wire.begin(9600);
	mpl115a2.begin();
}

/*******************************************
 *
 *    Name:        d_Sensors_sampleBatterymV     
 *    Returns:     Battery Voltage (mV)
 *    Parameter:   Nothing
 *    Description: Checks the battery voltage.
 *
 ******************************************/
long d_Sensors_sampleBatterymV(void){
	long value = 0;
	value = analogRead(_PIN_BATT_V)*5000.0/1023;
	return value;
}

/*******************************************
 *
 *    Name:        d_Sensors_samplePanelmV 
 *    Returns:     Panel Voltage (mV)
 *    Parameter:   Nothing
 *    Description: Checks the Solar Panel voltage.
 *
 ******************************************/
long d_Sensors_samplePanelmV(void){
	long value = 0;
	value = 2*analogRead(_PIN_SOLAR_V)*5000.0/1023;
	return value;
}

/*******************************************
 *
 *    Name:        d_Sensors_sampleSolarIrrmV 
 *    Returns:     Solar Irradiance Voltage (mV)
 *    Parameter:   Nothing
 *    Description: Checks the Solar Irradiance level.
 *
 ******************************************/
long d_Sensors_sampleSolarIrrmV(void){
	int value = 0;
	int PGA = 1; //Value should be equal to the gain indicated by
                     //the gain multiplier MCP342X_GAIN_#X
		     //Where # is the gain multiplier
	PyroADC_D.configure(MCP342X_MODE_CONTINUOUS | MCP342X_CHANNEL_1 |
				MCP342X_SIZE_16BIT | MCP342X_GAIN_1X);
	PyroADC_D.startConversion();
	PyroADC_D.getResult(&value);
	value = (value * (62.5/PGA))*1000;
	return value;
}

/*******************************************
 *
 *    Name:        d_Sensors_samplePressurepa 
 *    Returns:     Weather Pressure (pa)
 *    Parameter:   Nothing
 *    Description: Checks the current Pressure.
 *
 ******************************************/
long d_Sensors_samplePressurepa(void){
	long value = 0;
	value = mpl115a2.getPressure()*1000;
	return value;
}

/*******************************************
 *
 *    Name:        d_Sensors_Humiditypct 
 *    Returns:     Humidity (pct)
 *    Parameter:   Nothing
 *    Description: Checks the current Humidity.
 *
 ******************************************/
long d_Sensors_sampleHumiditypct(void){
	long value = 0;
	hih6131.update();
	value = hih6131.getHumidity();
	return value;
}

/*******************************************
 *
 *    Name:        d_Sensors_sampleTempdecic 
 *    Returns:     Temperature (Degrees C)
 *    Parameter:   Nothing
 *    Description: Checks the current Temperature.
 *
 ******************************************/
long d_Sensors_sampleTempdecic(void){
	long value = 0;
	value = mpl115a2.getTemperature()*10;
	return value;
}
