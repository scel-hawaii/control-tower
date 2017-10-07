/*******************************
 *
 * File: gg_board.h
 *
 * Contains struct for Dragonfruit packet, heartbeat, and board
 *
 ******************************/

#include "gg_dev_digi_xbee.h"
#include "gg_dev_apogee_SP212_irradiance.h"
#include "gg_dev_battery.h"
#include "gg_dev_solar_panel.h"
#include "gg_dev_eeprom_node_address.h"
#include "gg_dev_adafruit_BME280_temperature.h"
#include "gg_dev_adafruit_BME280_humidity.h"
#include "gg_dev_adafruit_BME280_pressure.h"

#ifndef gg_BOARD_H
#define gg_BOARD_H

struct gg_packet{
    uint16_t schema;
    uint16_t node_address;                             // Address of Arduino
    uint32_t uptime_milliseconds;                       // Time since start of program
    uint16_t battery_millivolts;                        // Battery Voltage (in milli volts)
    uint16_t panel_millivolts;                          // Panel Voltage (in milli volts)
    uint32_t bme280_pressure_pascals;                   // Pressure Value (in pascals)
    uint16_t bme280_temperature_kelvin;                // Temperature Value (in Kelvin)
    uint16_t bme280_humidity_percent;                  // Humidity Value (in percentage)
    uint16_t sp215_irradiance_watts_per_square_meter;  // Solar Irradiance Value (in W/m^2)
};

struct gg_heartbeat_packet{
    uint16_t schema;
    uint16_t node_address;       // Address of Arduino
    uint32_t uptime_milliseconds;       // Time since start of program
    uint16_t battery_millivolts;         // Battery Voltage (in milli volts)
};

struct gg_board{
    void (*setup)(struct gg_board* b);
    void (*post)(void);
    void (*sample)(struct gg_board* b);
    void (*run_cmd)(struct gg_board* b);
    void (*print_build_opts)(void);
    void (*tx)(struct gg_board* b);
    int (*ready_tx)(struct gg_board* b);
    int (*ready_sample)(struct gg_board* b);
    int (*ready_run_cmd)(struct gg_board* b);

    int (*ready_heartbeat_tx)(struct gg_board* b);
    void (*heartbeat_tx)(struct gg_board* b);

    unsigned long prev_sample_ms;
    unsigned long prev_heartbeat_ms;
    int sample_count;
    uint16_t node_address;
    struct gg_packet data_packet;
};


void gg_board_init(struct gg_board*);

#endif
