#include "ga23_dev_xbee.h"
#include "ga23_dev_sht1x.h"
#include "ga23_dev_bmp085.h"

#ifndef GA23_BOARD_H
#define GA23_BOARD_H

typedef struct ga23_board_def {
    void (*setup)(void);
    void (*post)(void);
    void (*sample)(void);
    void (*print_build_opts)(void);
} ga23_board;

void ga23_board_init(ga23_board*);
static void ga23_board_print_build_opts();
static void ga23_board_setup();
static void ga23_board_post();
static void ga23_board_sample();

#endif
