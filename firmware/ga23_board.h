#include "ga23_dev_xbee.h"
#include "ga23_dev_sht1x.h"
#include "ga23_dev_bmp085.h"
#include "ga23_dev_apogee_sp212.h"
#include "ga23_dev_batt.h"
#include "ga23_dev_spanel.h"
#include "ga23_dev_eeprom_naddr.h"

#ifndef GA23_BOARD_H
#define GA23_BOARD_H

struct ga23_packet{
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

struct ga23_board{
    void (*setup)(struct ga23_board* b);
    void (*post)(void);
    void (*sample)(struct ga23_board* b);
    void (*run_cmd)(struct ga23_board* b);
    void (*print_build_opts)(void);
    void (*tx)(struct ga23_board* b);
    int (*ready_tx)(struct ga23_board* b);
    int (*ready_sample)(struct ga23_board* b);
    int (*ready_run_cmd)(struct ga23_board* b);
    unsigned long prev_sample_ms;
    int sample_count;
    uint16_t node_addr;
    struct ga23_packet data_packet;
};


void ga23_board_init(struct ga23_board*);


#endif
