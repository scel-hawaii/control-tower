/*******************************************
 *
 *    File: config.cpp
 *    REIS Weatherbox Firmware
 *
 *    File contains configuring function
 *        pointers in accordance to the
 *        generation the code will be
 *        programmed to
 *
 ******************************************/

/* Program Libraries */
#include "config.h"
#include "sensors.h"


/*******************************************
 *
 *    Name:        Gen_config
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Checks the generation and assigns
 *                     the function pointers to the
 *                     appropriate functions.
 *
 *
 ******************************************/
void Gen_config(void){

    /* Check Generation & Assign Sensor Functions */
    #ifdef APPLE
        Sensors_init = &a_Sensors_init;
	Sensors_sampleBatterymV = &a_Sensors_sampleBatterymV;
	Sensors_samplePanelmV = &a_Sensors_samplePanelmV;
	Sensors_sampleSolarIrrmV = &a_Sensors_sampleSolarIrrmV;
	Sensors_samplePressurepa = &a_Sensors_samplePressurepa;
	Sensors_sampleHumiditypct = &a_Sensors_sampleHumiditypct;
	Sensors_sampleTempdecic = &a_Sensors_sampleTempdecic;
    #elif CRANBERRY
    #elif DRAGONFRUIT
    #endif

}
