#include "gd_dev_xbee.h"
#include "gd_dev_honeywell_HIH6131.h"
#include "gd_dev_apogee_sp215.h"
#include "gd_dev_batt.h"
#include "gd_dev_spanel.h"
#include "gd_dev_eeprom_naddr.h"
#include "gd_dev_adafruit_MPL115A2_temp.h"
#include "gd_dev_adafruit_MPL115A2_press.h"
#include <Arduino.h>

#define _PIN_SEN_EN_ 4

#ifndef GD_BOARD_H
#define GD_BOARD_H

struct gd_packet{
  uint16_t schema;
  uint16_t node_addr;         // Address of Arduino
  uint32_t uptime_ms;         // Time since start of program
  uint16_t batt_mv;           // Battery Voltage (in milli volts)
  uint16_t panel_mv;          // Panel Voltage (in milli volts)
  uint32_t apogee_sp215;      // Solar radiance
  uint16_t mpl115a2t1_temp;    // Temperature (centiKelvin)
  uint16_t hih6131_humidity_pct;  // Humidity (percentage)
  uint32_t mpl115a2t1_press;  // Pressure (Pa)
};

struct gd_heartbeat_packet{
    uint16_t schema;
    uint16_t node_addr;             // Address of Arduino
    uint32_t uptime_ms;             // Time since start of program
    uint16_t batt_mv;               // Battery Voltage (in milli volts)
};


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
    uint16_t node_addr;
    struct gd_packet data_packet;
};


void gd_board_init(struct gd_board*);

#endif
