/****************************************
 *
 *    File: utilities.cpp
 *    REIS Weatherbox Firmware
 *
 *    File containing utility functions
 *
 ****************************************/

/* Program Libraries */
#include "utilities.h"

/*****************************************
 *
 *    Name: chk_overflow
 *    Returns: 0 or 1
 *    Parameter: Current and previous millis() times
 *    Description: Compares the previous runtime with the current runtime to
 *                 check if an overflow occured
 *
 ****************************************/

int chk_overflow(unsigned long current_value, unsigned long previous_value){
    if(current_value < previous_value){
        return TRUE;
    }
    else{
        return FALSE;
    }
}


/********************************************
 *
 *    Name: sampleBatteryVoltage
 *    Returns: An averaged battery voltage
 *    Parameter: None.
 *    Description: Samples the battery ADC voltage a number of times and
 *                 averages it
 *
 *******************************************/
long sampleBatteryVoltage(void){
    
    /* Variable declarations */
    double temp;
    int i;

    for(i = 0; i < ADC_SAMPLE_NUM; i++){
      
        temp += analogRead(_PIN_BATT_V);
    }

    temp = temp/ADC_SAMPLE_NUM;
    return ((temp*5000.0/1023));
}

/*******************************************
 *
 *    Name: initHealthSamples
 *    Returns: Nothing.
 *    Parameter: None.
 *    Description: Initialize our battery sample by averaging 200 samples
 *                 then sending it to the Low Pass Filter by making it
 *                 the initial sample
 *
 *******************************************/
void initHealthSamples(void){
  
    /* Variable Declaration */
    int i;
    long battery_sample = 0;
    long solar_sample = 0;

    /* Sample 200 times */
    for(i = 0; i < 200; i++){
        battery_sample += analogRead(_PIN_BATT_V);
        solar_sample += analogRead(_PIN_APOGEE_V);
    }

    /* Average the samples */
    battery_sample = battery_sample/200;
    solar_sample = solar_sample/200;

    /* Initialize Low Pass Filter with sample */
    LPF_filter_init(&G_battery_filter, (float)battery_sample, BATT_LOWPASS_ALPHA);
    LPF_filter_init(&G_solar_filter, (float)solar_sample, BATT_LOWPASS_ALPHA);
}


/******************************************
 *
 *    Name: chk_health
 *    Returns: GOOD_SOLAR, NORMAL, POOR
 *    Parameter: None.
 *    Description: Compares current output to defined thresholds to determine
 *                 the state of health
 *
 *****************************************/
int chkHealth(void){

    int apogee_voltage = 0, panel_voltage = 0;

    //Read current and panel voltage
    apogee_voltage = LPF_get_current_output(&G_solar_filter);
    panel_voltage = 2*analogRead(_PIN_SOLAR_V);

    //Compare current and voltages to threshold value
    if(LPF_get_current_output(&G_battery_filter) >= THRESH_GOOD_BATT_V)
    {
        return NORMAL;
    }
    else if(apogee_voltage >= THRESH_GOOD_APOGEE_V ||
                panel_voltage >= THRESH_GOOD_PANEL_V)
    {
        return GOOD_SOLAR;
    }
    else
    {
        return POOR;
    }
}

/******************************************
 *
 *    Name: sendHealth
 *    Returns: Nothing.
 *    Parameter: Nothing
 *    Description: Transmits health data
 *
 ******************************************/
void sendHealth(void){
    
    long transmit_health = 600000;
    unsigned long transmit_timer = 0;

    if(millis() - G_health_transmit_timer >= transmit_health){

        //Power on system to transmit health data
        pstate_system(_ACTIVE);
		
        //Wait for the system to fully turn on
        transmit_timer = millis();
        int wake_time = 3000;
        while((millis() - transmit_timer) <= wake_time);

        //Transmit health data
        health_data_transmit();

        //Power off system again until next health data transmission
        pstate_system(_POWER_SAVE);

        //Update time since last health transmission
        G_health_transmit_timer = millis();
    }
}

/******************************************
 *
 *    Name: health_data_transmit
 *    Returns: Nothing.
 *    Parameter: None.
 *    Description: This function calls two other functions 
 *                 1) get the packet health, then
 *                 2) transmit the packet health
 *
 ******************************************/
void health_data_transmit(void){

    getPacketHealth();
    transmitPacketHealth();
}

/******************************************
 *
 *    Name: getPacketHealth
 *    Returns: Nothing.
 *    Parameter: None.
 *    Description: Retrieves packet health by utilizing schema_health.
 *
 ******************************************/
void getPacketHealth(void){
   
    //!!!GLOBAL USE!!!
    G_health.schema = 5;
    G_health.address = EEPROM.read(2) | (EEPROM.read(3) << 8);
    G_health.uptime_ms = millis();
    G_health.batt_mv = 1000*(analogRead(_PIN_BATT_V)*5/1023);
}

/******************************************
 *
 *    Name: transmitPacketHealth
 *    Returns: Nothing.
 *    Parameter: None.
 *    Description: Transmits the packet health.
 *
 ******************************************/
void transmitPacketHealth(void)
{
    /* Payload to send */
    uint8_t payload[MAX_SIZE];

    /* Obtain address of receiving end */
    XBeeAddress64 addr64 = XBeeAddress64(0,0);
    
    memset(payload, '\0', sizeof(payload));
    memcpy(payload, &G_health, sizeof(G_health));
    ZBTxRequest zbtx = ZBTxRequest(addr64, payload, sizeof(G_health));
    G_xbee.send(zbtx);
}


/************************* Power Management Functions *************************/

/********************************************
 *
 *    Name: pstate_system
 *    Returns: Nothing.
 *    Parameter: state
 *    Description: Given an integer (0 or 1),  this function will switch the 
 *                 sleep state for the xbee
 *                 and the power state for the sensor array. 
 *
 *******************************************/
void pstate_system(int state){

    P_STATE power_state;

    if(state == _ACTIVE){

        pstate_xbee(_ON, &power_state);
        pstate_sensors_array(_ON, &power_state);
    }
    else if(state == _POWER_SAVE){
    
        pstate_xbee(_OFF, &power_state);
        pstate_sensors_array(_OFF, &power_state);
    }
}


/*******************************************
 *
 *    Name: pstate_xbee
 *    Returns: Nothing.
 *    Parameter: state, P_STATE *power_state
 *    Description: Given an integer (0 or 1) this function will switch 
 *                 the sleep state for the xbee.
 *                 power_state is of type P_STATE which is a struct 
 *                 that has integer variables xbee and
 *                 sensor_array. This function sets the xbee variable
 *                 to 0 or 1, then calls the sync
 *                 function. 
 *
 ******************************************/
void pstate_xbee(int state, P_STATE *power_state){

    (*power_state).xbee = state;
    sync_pstate(*power_state);
}

/******************************************
 *
 *    Name: pstate_sensors_array
 *    Returns: Nothing
 *    Parameter: state, P_STATE *power_state
 *    Description: Given an integer (0 or 1) this function will 
 *                 switch the power state for the sensor
 *                 array. power_state is of type P_STATE which 
 *                 is a struct that has integer variables
 *                 xbee and sensor_array. This function sets the 
 *                 sensor_array variable to 0 or 1, then
 *                 then calls the sync function.
 *
 *****************************************/
void pstate_sensors_array(int state, P_STATE *power_state){

    (*power_state).sensor_array = state;
    sync_pstate(*power_state);
}

/*****************************************
 *
 *    Name: sync_pstate
 *    Returns: Nothing.
 *    Parameter: None.
 *    Description: This function uses digitalWrite to set the 
 *                 pins on the XBEE(??) which switches the
 *                 power state for the sensor array and the 
 *                 xbee sleep mode.
 *
 ****************************************/
void sync_pstate(P_STATE power_state){

    digitalWrite(_PIN_XBEE_SLEEP, !power_state.xbee);
    digitalWrite(_PIN_SEN_EN, power_state.sensor_array);	
}

/*****************************************************************************/




/****************************Low Pass Filter Functions************************/

/*****************************************
 *
 *    Name:        LPF_filter_init
 *    Returns:     Nothing
 *    Parameter:   LowPassFilter *f, float output, float alpha
 *    Description: Initializes the filter
 *
 *****************************************/
void LPF_filter_init(LowPassFilter *f, float output, float alpha){

    /* Variable Initialization */
    f->output = output;
    f->alpha = alpha;
}

/******************************************
 *
 *    Name:        LPF_update_filter
 *    Returns:     Output of the filter
 *    Parameter:   LowPassFilter *f, float new_value
 *    Description: Updates the filter with a new value.
 *
 *****************************************/
float LPF_update_filter(LowPassFilter *f, float new_value){

    /* Update output */
    f->output = (f->alpha)*new_value + (1 - f->alpha)*f->output;

    /* Return the output */
    return (f->output);
}

/******************************************
 *
 *    Name:        LPF_get_current_output
 *    Returns:     Current output of the flter
 *    Parameter:   LowPassFilter *f
 *    Description: Retrieves the most up-to-date output of the filter
 *
 ******************************************/
float LPF_get_current_output(LowPassFilter *f){

    /* Return output stored in the struct */
    return (f->output);
}
