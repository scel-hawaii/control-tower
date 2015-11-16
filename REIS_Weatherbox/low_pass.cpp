/*******************************************
 *
 *    File: low_pass.cpp
 *    REIS Weatherbox Firmware
 *
 *    File for low pass filter functions
 *
 ******************************************/

/* Program Libraries */
#include "low_pass.h"


/*******************************************
 *
 *    Name:        LPF_filter_init
 *    Returns:     Nothing
 *    Parameter:   LowPassFilter *f, float output, float alpha
 *    Description: Initializes the filter.
 *
 ******************************************/
void LPF_filter_init(LowPassFilter *f, float output, float alpha){

    /* Variable Initialization */
    f->output = output;
    f->alpha = alpha;
}

/*******************************************
 *
 *    Name:        LPF_update_filter
 *    Returns:     Output of the filter
 *    Parameter:   LowPassFilter *f, float new_value
 *    Description: Updates the filter with a new value.
 *
 ******************************************/
float LPF_update_filter(LowPassFilter *f, float new_value){

    /* Update output */
    f->output = (f->alpha)*new_value + (1 - f->alpha)*f->output;

    /* Return the output */
    return (f->output);
}

/*******************************************
 *
 *    Name:        LPF_get_current_output
 *    Returns:     Current output of the filter
 *    Parameter:   LowPassFilter *f
 *    Description: Retrievers the most up-to-date output
 *                     of the filter.
 *
 ******************************************/
float LPF_get_current_output(LowPassFilter *f){

    /* Return output stored in the struct */
    return (f->output);
}
