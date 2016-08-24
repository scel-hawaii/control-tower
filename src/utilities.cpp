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
#ifndef GA23
    if(current_value < previous_value){
        return TRUE;
    }
    else{
        return FALSE;
    }
#endif
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
#ifndef GA23

    P_STATE power_state;

    if(state == _ACTIVE){

        pstate_xbee(_ON, &power_state);
        pstate_sensors_array(_ON, &power_state);
    }
    else if(state == _POWER_SAVE){
    
        pstate_xbee(_OFF, &power_state);
        pstate_sensors_array(_OFF, &power_state);
    }
#endif
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
#ifndef GA23
    (*power_state).xbee = state;
    sync_pstate(*power_state);
#endif
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
#ifndef GA23
    (*power_state).sensor_array = state;
    sync_pstate(*power_state);
#endif
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
#ifndef GA23
    digitalWrite(_PIN_XBEE_SLEEP, !power_state.xbee);
    digitalWrite(_PIN_SEN_EN, power_state.sensor_array);	
#endif
}
