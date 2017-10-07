/*******************************
 *
 * File: gd_board.h
 *
 * Contains struct for Dragonfruit packet, heartbeat, and board
 *
 ******************************/

#include "gd_dev_digi_xbee.h"
#include "gd_dev_honeywell_HIH6131_humidity.h"
#include "gd_dev_apogee_SP215_irradiance.h"
#include "gd_dev_battery.h"
#include "gd_dev_solar_panel.h"
#include "gd_dev_eeprom_node_address.h"
#include "gd_dev_adafruit_MPL115A2_temperature.h"
#include "gd_dev_adafruit_MPL115A2_pressure.h"
#include <Arduino.h>

#define _PIN_SEN_EN_ 4

#ifndef GD_BOARD_H
#define GD_BOARD_H

struct gd_packet{
  uint16_t schema;
  uint16_t node_address;                             // Address of Arduino
  uint32_t uptime_milliseconds;                       // Time since start of program
  uint16_t battery_millivolts;                        // Battery Voltage (in milli volts)
  uint16_t panel_millivolts;                          // Panel Voltage (in milli volts)
  uint32_t sp215_irradiance_watts_per_square_meter;  // Solar radiance
  uint16_t mpl115a2t1_temperature_kelvin;            // Temperature (centiKelvin)
  uint16_t hih6131_humidity_percent;                 // Humidity (percentage)
  uint32_t mpl115a2t1_pressure_pascals;               // Pressure (Pa)
};

struct gd_heartbeat_packet{
    uint16_t schema;
    uint16_t node_address;             // Address of Arduino
    uint32_t uptime_milliseconds;       // Time since start of program
    uint16_t battery_millivolts;        // Battery Voltage (in milli volts)
};

/* Heartbeat 2.0 Packet
struct ga_heartbeat_packet {
  uint16_t schema;
  uint16_t node_addr;
  uint32_t uptime_ms;
  uint16_t batt_mv;
  float latitude;
  float longitude;
  float altitude;
  uint8_t generation;
  uint8_t version;
  uint8_t revision;
  uint32_t deployment_date; //Epoch date
};
*/

struct gd_board{
    void (*setup)(struct gd_board* b);
    void (*post)(void);
    void (*sample)(struct gd_board* b);
    void (*run_cmd)(struct gd_board* b);
    void (*print_build_opts)(void);
    void (*tx)(struct gd_board* b);
    int (*ready_tx)(struct gd_board* b);
    int (*ready_sample)(struct gd_board* b);
    int (*ready_run_cmd)(struct gd_board* b);

    int (*ready_heartbeat_tx)(struct gd_board* b);
    void (*heartbeat_tx)(struct gd_board* b);

    unsigned long prev_sample_ms;
    unsigned long prev_heartbeat_ms;
    int sample_count;
    uint16_t node_address;
    struct gd_packet data_packet;
};

void gd_board_init(struct gd_board*);
#endif
