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
#include "sensors.h"
#include "transmit.h"
#include "routines.h"
#include "config.h"

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
    
    #ifndef APPLE
        pinMode(_PIN_SEN_EN, OUTPUT);
    #endif
    
    /* Check Generation & Assign Sensor Functions */
    #ifdef APPLE
        Sensors_init = &a_Sensors_init;
        Sensors_sampleBatterymV = &a_Sensors_sampleBatterymV;
        Sensors_samplePanelmV = &a_Sensors_samplePanelmV;
        Sensors_sampleSolarIrrmV = &a_Sensors_sampleSolarIrrmV;
        Sensors_samplePressurepa = &a_Sensors_samplePressurepa;
        Sensors_sampleHumiditypct = &a_Sensors_sampleHumiditypct;
        Sensors_sampleTempdecic = &a_Sensors_sampleTempdecic;
    #elif defined(CRANBERRY)
        Sensors_init = &c_Sensors_init;
        Sensors_sampleBatterymV = &c_Sensors_sampleBatterymV;
        Sensors_samplePanelmV = &c_Sensors_samplePanelmV;
        Sensors_sampleSolarIrrmV = &c_Sensors_sampleSolarIrrmV;
        Sensors_samplePressurepa = &c_Sensors_samplePressurepa;
        Sensors_sampleHumiditypct = &c_Sensors_sampleHumiditypct;
        Sensors_sampleTempdecic = &c_Sensors_sampleTempdecic;
    #elif defined(DRAGONFRUIT)
        Sensors_init = &d_Sensors_init;
        Sensors_sampleBatterymV = &d_Sensors_sampleBatterymV;
        Sensors_samplePanelmV = &d_Sensors_samplePanelmV;
        Sensors_sampleSolarIrrmV = &d_Sensors_sampleSolarIrrmV;
        Sensors_samplePressurepa = &d_Sensors_samplePressurepa;
        Sensors_sampleHumiditypct = &d_Sensors_sampleHumiditypct;
        Sensors_sampleTempdecic = &d_Sensors_sampleTempdecic;
    #endif
}

/*******************************************
 *
 *    Name:        Transmit_config
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Checks the transmission configuration
 *                     and assigns the function pointers 
 *                     to the appropriate functions.
 *
 ******************************************/
void Transmit_config(void){

    /* Enable XBee */
    #ifndef APPLE
        pinMode(_PIN_XBEE_EN, OUTPUT);
    #endif

    /* Assign Transmit functions based on transmission config */
    #ifdef UART
        /* Transmission */
        Packet_Clear = &Packet_ClearUART;
        Packet_Con = &Packet_ConUART;
        Packet_Transmit = &Packet_TransmitUART;

	/* Routine */
	Normal_Routine = &Normal_RoutineUART;

    #elif defined(BINARY)
        /* Transmission */
        Packet_Clear = &Packet_ClearBIN;
        Packet_Con = &Packet_ConBIN;
        Packet_Transmit = &Packet_TransmitBIN;

	/* Routine */
	Normal_Routine = &Normal_RoutineBIN;
    #endif
}
