/*******************************
 *
 * File: gc_board.h
 *
 * Contains struct for Cranberry packet, heartbeat, and board
 *
 ******************************/

#include "gc_dev_digi_xbee.h"
#include "gc_dev_battery.h"
#include "gc_dev_solar_panel.h"
#include "gc_dev_eeprom_node_address.h"
#include "gc_dev_apogee_SP212_irradiance.h"
#include "gc_dev_honeywell_HIH6131_temperature.h"
#include "gc_dev_honeywell_HIH6131_humidity.h"
#include "gc_dev_adafruit_MPL115A2_pressure.h"

#ifndef GC_BOARD_H
#define GC_BOARD_H

#define _PIN_SEN_EN 4

struct gc_packet{
    uint16_t schema;
    uint16_t node_address;                             // Address of Arduino
    uint32_t uptime_milliseconds;                       // Time since start of program
    uint16_t battery_millivolts;                        // Battery Voltage (in milli volts)
    uint16_t panel_millivolts;                          // Panel Voltage (in milli volts)
    uint16_t sp212_irradiance_watts_per_square_meter;  // Solar Irradiance (in watts per meter squared)
    uint16_t hih6131_temperature_kelvin;               // Temperature Value (Celsius)
    uint16_t hih6131_humidity_percent;                 // Humidity Value (percentage)
    uint32_t mpl115a2t1_pressure_pascals;               // Pressure Value (Pascal)
};

struct gc_heartbeat_packet{
    uint16_t schema;
    uint16_t node_address;           // Address of Arduino
    uint32_t uptime_milliseconds;     // Time since start of program
    uint16_t battery_millivolts;      // Battery Voltage (in milli volts)
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

struct gc_board{
    void (*setup)(struct gc_board* b);
    void (*post)(void);
    void (*sample)(struct gc_board* b);
    void (*run_cmd)(struct gc_board* b);
    void (*print_build_opts)(void);
    void (*tx)(struct gc_board* b);
    int (*ready_tx)(struct gc_board* b);
    int (*ready_sample)(struct gc_board* b);
    int (*ready_run_cmd)(struct gc_board* b);

    int (*ready_heartbeat_tx)(struct gc_board* b);
    void (*heartbeat_tx)(struct gc_board* b);

    unsigned long prev_sample_ms;
    unsigned long prev_heartbeat_ms;
    int sample_count;
    uint16_t node_address;
    struct gc_packet data_packet;
};

void gc_board_init(struct gc_board*);

#endif
