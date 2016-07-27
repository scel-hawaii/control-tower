#include "ga23_dev_xbee.h"
#include "ga23_dev_sht1x.h"
#include "ga23_dev_bmp085.h"

#ifndef GA23_BOARD_H
#define GA23_BOARD_H

struct ga23_board{
    void (*setup)(void);
    void (*post)(void);
    void (*sample)(struct ga23_board* b);
    void (*print_build_opts)(void);
    void (*tx)(struct ga23_board* b);
    int (*ready_tx)(struct ga23_board* b);
    int sample_count;
};

void ga23_board_init(ga23_board*);
static void ga23_board_print_build_opts();
static void ga23_board_setup();
static void ga23_board_post();
static void ga23_board_sample(ga23_board* b);
static int ga23_board_ready_tx(ga23_board* b);
static void ga23_board_tx(ga23_board* b);

#endif
