/*******************************
 *
 *    File: utilities.cpp
 *    REIS Weatherbox Firmware
 *
 *    File containing utility functions
 *
 ******************************/


#include "utilities.h"


/*******************************
 *
 *    Name: chk_overflow
 *    Returns: 0 or 1
 *    Parameter: Current and previous millis() times
 *    Description: Compares the previous runtime with the current runtime to
 *                 check if an overflow occured
 *
 ******************************/

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
 *******************************/

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


/**********************************
 *
 *    Name: chk_health
 *    Returns: GOOD_SOLAR, NORMAL, POOR
 *    Parameter: LowPassFilter* f
 *    Description: 
 *
 *********************************/

int chkHealth(void)
{
	int apogee_voltage = 0, panel_voltage = 0;

	apogee_voltage = LPF_get_current_output(&solar_filter);
	panel_voltage = 2*analogRead(_PIN_SOLAR_V);

	if(LPF_get_current_output(&battery_filter) >= THRESH_GOOD_BATT_V)
		return NORMAL;
#ifdef HEALTH_GOOD_APOGEE
	else if(apogee_voltage >= THRESH_GOOD_APOGEE_V)
#else //HEALTH_GOOD_PANEL
	else if(panel_voltage >= THRESH_GOOD_PANEL_V)
#endif
		return GOOD_SOLAR;
	else
		return POOR;
}


/*********************************
 *
 *    Name: cofigureADC 
 *    Returns: Nothing.
 *    Parameter: None.
 *    Description: Configures the ADC. Normally in the Arduino IDE, 
 *                 we don't have to worry about this but we change the 
 *                 registers to speed up the ADC sample times a little. 
 *                 More documentation available online.
 *
 ********************************/

/* Define various ADC prescaler */
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 <<ADPS2) | (1 << ADPS1) | (1 << ADPS0);

void configureADC(void)
{
	/* Setup faster ADC */
	ADCSRA &= ~PS_128; //remove bit set by Arduino library
	//you can choose a prescaler from above
	// PS_16, PS_32, PS_64, PS_128
	ADCSRA |= PS_64; //set our own prescaler to 64
}
