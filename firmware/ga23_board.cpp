#include "ga23_board.h"

static void ga23_board_print_build_opts();
static void ga23_board_setup();
static void ga23_board_post();
static void ga23_board_sample(struct ga23_board* b);
static int ga23_board_ready_tx(struct ga23_board* b);
static void ga23_board_tx(struct ga23_board* b);

void ga23_board_init(ga23_board *b){
    b->print_build_opts = &ga23_board_print_build_opts;
    b->setup = &ga23_board_setup;
    b->post = &ga23_board_post;
    b->sample = &ga23_board_sample;
    b->tx = &ga23_board_tx;
    b->ready_tx = &ga23_board_ready_tx;
    b->sample_count = 0;
}

static void ga23_board_print_build_opts()
{
    Serial.begin(9600);
    Serial.println("Board Options ");
    Serial.println("Generation: apple23");
}

static void ga23_board_setup(){
    Serial.begin(9600);
    Serial.println("Board Setup Init");
    ga23_dev_xbee_open();
    ga23_dev_sht1x_open();
    ga23_dev_bmp085_open();
    ga23_dev_apogee_sp212_open();
    ga23_dev_batt_open();

    delay(100);
    Serial.println("Board Setup Done");
}

// power on self test
static void ga23_board_post(){
    Serial.println("POST Begin");

    // Check sht1x
    Serial.println("POST: Check sht1x value");
    int sht1x_val = ga23_dev_sht1x_read();

    Serial.print("POST: sht1x value - ");
    Serial.println(sht1x_val);

    if(sht1x_val < 800){
        Serial.println("POST: Error: Humidity out of range");
    }

    // Check BMP085
    Serial.println("POST: Check bmp085 value");
    int bmp085_val = ga23_dev_bmp085_read();

    Serial.print("POST: bmp085 value - ");
    Serial.println(bmp085_val);

    if(bmp085_val < 800){
        Serial.println("POST: Error: bmp085 pressure out of range");
    }

    // Check apogee_sp212
    Serial.println("POST: Check apogee_sp212 value");
    int apogee_sp212_val = ga23_dev_apogee_sp212_read();

    Serial.print("POST: apogee_sp212 solar irr value - ");
    Serial.println(apogee_sp212_val);

    if(apogee_sp212_val < 100){
        Serial.println("POST: Error: apogee solar irr out of range");
    }

    // Check batt
    Serial.println("POST: Check batt value");
    int batt_val = ga23_dev_batt_read();

    Serial.print("POST: batt value - ");
    Serial.println(batt_val);

    if(batt_val < 100){
        Serial.println("POST: Error: batt out of range");
    }

    Serial.println("POST End");

}

static void ga23_board_sample(struct ga23_board* b){
    Serial.println("Sample Start");
    Serial.println(b->sample_count);
    Serial.println("Sample End");
    b->sample_count++;
}

static int ga23_board_ready_tx(struct ga23_board* b){
    if(b->sample_count > 59){
        return 1;
    }
    else{
        return 0;
    }
}

static void ga23_board_tx(struct ga23_board* b){
    Serial.println("Sample Transmit");
    b->sample_count = 0;
}

static void ga23_board_soft_rst(){
    asm volatile ("jmp 0");
}
