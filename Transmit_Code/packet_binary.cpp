#include "schema.h"
#include "sensors.h"

void clear_packet(void)
{
/* Given: Nothing.
   Returns: Nothing.
   Actions: Clears the packet by setting all variables to 0.
*/

    /* Variable Declaration/Initialization */
    int i = 0;
    
    /* Set all values in packet of schema3 type to 0 */
    packet.schema = 3;
    packet.address = address;
    packet.uptime_ms = 0;
    packet.n = 0;
    packet.bmp085_press_pa = 0;
    packet.bmp085_temp_decic = 0;
    packet.humidity_centi_pct = 0;
    
    for(i=0; i<60; i++)
    {
       packet.batt_mv[i/10] = 0;
       packet.panel_mv[i/10] = 0;
       packet.apogee_w_m2[i/3] = 0;
    }
}

void samplePacketBinary(void)
{
/* Given: Nothing.
   Returns: Nothing.
   Actions: This function samples for data and puts the results in a packet.
            The binary packet format can take up to 60 samples. Each subsequent
	    sample iterates the number of data points, allowing us to keep tracK
	    of how many samples we've already taken.
	    The sample function takes care of the stacking.

	    Note: Solar irradiance is sampled each second, and the other less
	    important data points can be sampled less frequently.
*/

    /* Variable Declaration/Initialization */
    int n = packet.n;
    int i;
    float batt_mv_raw = 0, panel_mv_raw = 0, apogee_raw = 0, pressure_raw = 0, 
    temperature_raw = 0, humidity_raw = 0;

    
    /* Check if millis() has overflowed */
    /* If the previous uptime is greater than the current millis(),
    an overflow has occured */
    unsigned long uptime = millis();
    packet.overflow_num += chk_overflow(uptime, packet.uptime_ms);
    packet.uptime_ms = uptime;

    /* Sample for data */
    batt_mv_raw = Sensors_sampleBatterymV();
    panel_mv_raw = Sensors_samplePanelmV();
    apogee_raw = Sensors_sampleSolarIrrmV();
    pressure_raw = Sensors_samplePressurepa();
    temperature_raw = Sensors_sampleTempdecic();
    humidity_raw = Sensors_sampleHumiditypct();

    /* Save results to the packet */
    packet.batt_mv[n/10] = batt_mv_raw;
    packet.panel_mv[n/10] = panel_mv_raw;
    packet.apogee_w_m2[n/3] = apogee_raw;
    packet.bmp085_press_pa = pressure_raw;
    packet.bmp085_temp_decic = temperature_raw;
    packet.humidity_centi_pct = humidity_raw;
    packet.n += 1;
}




