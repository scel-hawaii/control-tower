#include "gc_dev_xbee.h"
#include "gc_dev_sht1x.h"
#include "gc_dev_bmp085.h"
#include "gc_dev_apogee_sp212.h"
#include "gc_dev_batt.h"
#include "gc_dev_spanel.h"
#include "gc_dev_eeprom_naddr.h"

#ifndef GC_BOARD_H
#define GC_BOARD_H

struct gc_packet{
    uint16_t schema;
    uint16_t node_addr;           // Address of Arduino
    uint32_t uptime_ms;         // Time since start of program
    uint16_t batt_mv;           // Battery Voltage (in milli volts)
    uint16_t panel_mv;          // Panel Voltage (in milli volts)
    uint32_t bmp085_press_pa;   // Pressure Value (in pascals)
    int16_t bmp085_temp_decic;  // Temperature Value (in celsius)
    uint16_t humidity_centi_pct;
    uint16_t apogee_w_m2;
};

struct gc_heartbeat_packet{
    uint16_t schema;
    uint16_t node_addr;           // Address of Arduino
    uint32_t uptime_ms;         // Time since start of program
    uint16_t batt_mv;           // Battery Voltage (in milli volts)
};

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
    uint16_t node_addr;
    struct gc_packet data_packet;
};


void gc_board_init(struct gc_board*);


#endif
