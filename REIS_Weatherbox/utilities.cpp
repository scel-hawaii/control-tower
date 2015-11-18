/*******************************
 *
 *    File: utilities.cpp
 *    REIS Weatherbox Firmware
 *
 *    File containing utility functions
 *
*******************************/


#include "utilities.h"


/*******************************
 *
 *    Name: chk_overflow
 *    Returns: 0 or 1
 *    Parameter: Current and previous millis() times
 *    Description: Compares the previous runtime with the current runtime to
 *                 check if an overflow occured
 *
*******************************/

int chk_overflow(unsigned long current_value, unsigned long previous_value)
{
	if(current_value < previous_value)
		return TRUE;
	else
		return FALSE;
}


/*******************************
 *
 *    Name: sampleBatteryVoltage
 *    Returns: An averaged battery voltage
 *    Parameter: None.
 *    Description: Samples the battery ADC voltage a number of times and
 *                 averages it
 *
********************************/

long sampleBatteryVoltage(void)
{
  double temp;
  
  for(i=0; i < ADC_SAMPLE_NUM; i++)
  {
	temp += analogRead(_PIN_BATT_V);
  }

	temp = temp/ADC_SAMPLE_NUM;
	return ((temp*5000.0/1023));
}

/*********************************
 *
 *    Name: 
 *    Returns:
 *    Parameter:
 *    Description:
 *
*********************************/
















