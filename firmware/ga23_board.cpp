#include "ga23_board.h"

static void ga23_board_print_build_opts();
static void ga23_board_setup(struct ga23_board* b);
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
    b->node_addr = 0;


    // Initialize the packet
    b->data_packet.schema = 0;
    b->data_packet.node_addr = 0;
    b->data_packet.uptime_ms = 0;
    b->data_packet.batt_mv = 0;
    b->data_packet.panel_mv = 0;
    b->data_packet.bmp085_press_pa = 0;
    b->data_packet.bmp085_temp_decic = 0;
    b->data_packet.humidity_centi_pct = 0;
    b->data_packet.apogee_w_m2 = 0;
}

static void ga23_board_print_build_opts()
{
    Serial.begin(9600);
    Serial.println("Board Options ");
    Serial.println("Generation: apple23");
}

static void ga23_board_setup(struct ga23_board* b){
    Serial.begin(9600);
    Serial.println("Board Setup Init");

    // Open Devices
    ga23_dev_xbee_open();
    ga23_dev_sht1x_open();
    ga23_dev_bmp085_open();
    ga23_dev_apogee_sp212_open();
    ga23_dev_batt_open();
    ga23_dev_spanel_open();
    ga23_dev_eeprom_naddr_open();

    // load the address from the hardware
    b->node_addr = ga23_dev_eeprom_naddr_read();

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
    int32_t bmp085_val = ga23_dev_bmp085_read();

    Serial.print("POST: bmp085 value:  ");
    Serial.println(bmp085_val);

    if(bmp085_val < 800){
        Serial.println("POST: Error: bmp085 pressure out of range");
    }

    // Check BMP085 temperature
    Serial.println("POST: Check bmp085 temp");
    uint16_t bmp085_temp = ga23_dev_bmp085_read_temp();

    Serial.print("POST: bmp085 temp: ");
    Serial.println(bmp085_temp);

    if(bmp085_temp < 800){
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

    // check panel sensor value
    Serial.println("POST: check panel sensor value");
    int spanel_val = ga23_dev_spanel_read();
    Serial.print("POST: spanel value: ");
    Serial.println(spanel_val);

    if(spanel_val < 100){
        Serial.println("POST: ERROR: spanel value out of range");
    }

    Serial.println("POST End");

}

static void ga23_board_sample(struct ga23_board* b){
    Serial.println("Sample Start");
    Serial.println(b->sample_count);

    struct ga23_packet* data_packet = &(b->data_packet);
    data_packet->uptime_ms           = millis();
    data_packet->batt_mv             = ga23_dev_batt_read();
    data_packet->panel_mv            = ga23_dev_spanel_read();
    data_packet->bmp085_press_pa     = ga23_dev_bmp085_read();
    data_packet->bmp085_temp_decic   = ga23_dev_bmp085_read_temp();
    data_packet->humidity_centi_pct  = ga23_dev_sht1x_read();
    data_packet->apogee_w_m2         = ga23_dev_apogee_sp212_read();

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
    uint8_t payload[_GA23_DEV_XBEE_BUFSIZE_];
    struct ga23_packet data_packet = b->data_packet;

    Serial.println("Sample Transmit");

    memset(payload, '\0', sizeof(payload));
    memcpy(payload, &data_packet, sizeof(data_packet));

    ga23_dev_xbee_write(payload);

    // Reset the sample count
    b->sample_count = 0;
}

static void ga23_board_soft_rst(){
    asm volatile ("jmp 0");
}
