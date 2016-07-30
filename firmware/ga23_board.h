#include "ga23_dev_xbee.h"
#include "ga23_dev_sht1x.h"
#include "ga23_dev_bmp085.h"
#include "ga23_dev_apogee_sp212.h"

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

void ga23_board_init(struct ga23_board*);


#endif
