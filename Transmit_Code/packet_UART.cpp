/************************************
 *
 *    File: packetUART.cpp
 *    REIS Weatherbox Firmware
 *
 *    File containing packet organization (UART)
 *
*************************************/


/* Necessary Libraries */
#include "packet.h"


/************************************ 
 *
 *    Name: samplePacketUART  
 *    Returns: Nothing
 *    Parameter: Nothing
 *    Description: 
 *
************************************/

void samplePacketUART(void)
{
#ifdef PacketUART
	s = "{";
	s += "\"address\": ";
	s += String(address);
        s += ", \"uptime_ms\": ";
        s += String(millis());
        s += ", \"bmp085_temp_decic\": ";
        bmp085_temp_decic = bmp085.readTemperature()*10;
        s += String(bmp085_temp_decic);
        s += ", \"bmp085_press_pa\": ";
        bmp085_press_pa = bmp085.readPressure();
        s += String(bmp085_press_pa);
        s += ", \"batt_mv\": ";
        batt_mv = sampleBatteryVoltage();
        softserial.println(batt_mv);
        s += String(batt_mv);

	s += ", \"panel_mv\": ";
        panel_mv = 2*analogRead(1)*5000.0/1024;
        s += String(panel_mv);
        s += ", \"apogee_mv\": ";
        apogee_mv = analogRead(2)*5000.0/1024;
        s += String(apogee_mv);
        s += ", \"apogee_w_m2\": ";
        apogee_w_m2 = apogee_mv*5.0;
        s += String(apogee_w_m2);

	s += ", \"panel_ua\": ";
        panel_ua = ina219_Solar.getCurrent_mA()*1000;
        s += String(panel_ua);

	s += ", \"dallas_roof_c\": ";
        dallas_roof_sen.requestTemperatures();
        dallas_rooftemp_c = dallas_roof_sen.getTempCByIndex(0);
        s += String(dallas_rooftemp_c);

	s += ", \"dallas_amb_c\": ";
        dallas_amb_sen.requestTemperatures();
        dallas_ambtemp_c = dallas_amb_sen.getTempCByIndex(0);
        s += String(dallas_ambtemp_c);
        s += "}";
        s += "       ";		// it explodes without something here... omg wtf

#endif
}
