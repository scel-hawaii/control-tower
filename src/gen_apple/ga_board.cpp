#include "ga_board.h"

static void ga_board_print_build_opts();
static void ga_board_setup(struct ga_board* b);
static void ga_board_post();

static void ga_board_run_cmd(struct ga_board* b);
static int ga_board_ready_run_cmd(struct ga_board* b);

static void ga_board_sample(struct ga_board* b);
static int ga_board_ready_sample(struct ga_board* b);

static void ga_board_tx(struct ga_board* b);
static int ga_board_ready_tx(struct ga_board* b);

static int ga_board_ready_heartbeat_tx(struct ga_board* b);
static void ga_board_heartbeat_tx(struct ga_board* b);

void ga_board_init(ga_board *b){
    // Link functions to make them accessable
    b->print_build_opts = &ga_board_print_build_opts;
    b->setup = &ga_board_setup;
    b->post = &ga_board_post;
    b->sample = &ga_board_sample;
    b->ready_sample = &ga_board_ready_sample;
    b->tx = &ga_board_tx;
    b->ready_tx = &ga_board_ready_tx;
    b->run_cmd = &ga_board_run_cmd;
    b->ready_run_cmd = &ga_board_ready_run_cmd;

    b->ready_heartbeat_tx = &ga_board_ready_heartbeat_tx;
    b->heartbeat_tx = &ga_board_heartbeat_tx;

    b->sample_count = 0;
    b->node_addr = 0;
    b->prev_sample_ms = 0;

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

static void ga_board_print_build_opts()
{
    Serial.begin(9600);
    Serial.println("Board Opts");
    Serial.println("Gen: apple23");
}

static void ga_board_setup(struct ga_board* b){
    Serial.begin(9600);
    Serial.println("Board Setup Start");

    // Open Devices
    ga_dev_xbee_open();
    ga_dev_sht1x_open();
    ga_dev_bmp085_open();
    ga_dev_apogee_sp212_open();
    ga_dev_batt_open();
    ga_dev_spanel_open();
    ga_dev_eeprom_naddr_open();

    // load the address from the hardware
    b->node_addr = ga_dev_eeprom_naddr_read();

    delay(100);
    Serial.println("Board Setup Done");
}

// power on self test
static void ga_board_post(){
    Serial.println("POST Begin");

    // Display node addr
    Serial.print("P: node addr ");
    Serial.println((int) ga_dev_eeprom_naddr_read());

    // Check sht1x
    Serial.println("P: Check sht1x value");
    int sht1x_val = ga_dev_sht1x_read();

    Serial.print("P: sht1x value - ");
    Serial.println(sht1x_val);

    if(sht1x_val < 800){
        Serial.println("P: Error: Humidity out of range");
    }

    // Check BMP085
    Serial.println("P: Check bmp085 value");
    int32_t bmp085_val = ga_dev_bmp085_read();

    Serial.print("P: bmp085 value:  ");
    Serial.println(bmp085_val);

    if(bmp085_val < 800){
        Serial.println("P: Error: bmp085 pressure out of range");
    }

    // Check BMP085 temperature
    Serial.println("P: Check bmp085 temp");
    uint16_t bmp085_temp = ga_dev_bmp085_read_temp();

    Serial.print("P: bmp085 temp: ");
    Serial.println(bmp085_temp);

    if(bmp085_temp < 800){
        Serial.println("P: Error: bmp085 pressure out of range");
    }

    // Check apogee_sp212
    Serial.println("P: Check apogee_sp212 value");
    int apogee_sp212_val = ga_dev_apogee_sp212_read();

    Serial.print("P: apogee_sp212 solar irr value - ");
    Serial.println(apogee_sp212_val);

    if(apogee_sp212_val < 100){
        Serial.println("P: Error: apogee solar irr out of range");
    }

    // Check batt
    Serial.println("P: Check batt value");
    int batt_val = ga_dev_batt_read();

    Serial.print("P: batt value - ");
    Serial.println(batt_val);

    if(batt_val < 100){
        Serial.println("P: Error: batt out of range");
    }

    // check panel sensor value
    Serial.println("P: check panel sensor value");
    int spanel_val = ga_dev_spanel_read();
    Serial.print("P: spanel value: ");
    Serial.println(spanel_val);

    if(spanel_val < 100){
        Serial.println("P: ERROR: spanel value out of range");
    }

    Serial.println("POST End");

}

static void ga_board_sample(struct ga_board* b){
    Serial.println("Sample Start");
    Serial.println(b->sample_count);

    struct ga_packet* data_packet = &(b->data_packet);
    data_packet->uptime_ms           = millis();
    data_packet->batt_mv             = ga_dev_batt_read();
    data_packet->panel_mv            = ga_dev_spanel_read();
    data_packet->bmp085_press_pa     = ga_dev_bmp085_read();
    data_packet->bmp085_temp_decic   = ga_dev_bmp085_read_temp();
    data_packet->humidity_centi_pct  = ga_dev_sht1x_read();
    data_packet->apogee_w_m2         = ga_dev_apogee_sp212_read();

    Serial.println("Sample End");
    b->sample_count++;
}

static int ga_board_ready_tx(struct ga_board* b){
    const int max_samples = 20;
    if(b->sample_count > max_samples-1){
        return 1;
    }
    else{
        return 0;
    }
}

static int ga_board_ready_sample(struct ga_board* b){
    const int wait_ms = 3000;
    const int sample_delta = millis() - b->prev_sample_ms;

    if( sample_delta >= wait_ms){
        b->prev_sample_ms = millis();
        return 1;
    }
    else{
        return 0;
    }
}

static int ga_board_ready_run_cmd(struct ga_board* b){
    return Serial.available();
}

static void ga_board_run_cmd(struct ga_board* b){
    Serial.println("Enter CMD Mode");
    while(Serial.read() != '\n');
    while(1){
        if(Serial.available()){
            char input = Serial.read();
            Serial.print("GOT A CMD: ");
            Serial.println(input);
            while(Serial.read() != '\n');
            if(input == 'E') {
                break;
            }
            else{
                switch(input){
                    case 'T':
                        Serial.println("CMD Mode cmd");
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

static int ga_board_ready_heartbeat_tx(struct ga_board* b){
    const int wait_ms = 3000;
    int sample_delta = millis() - b->prev_heartbeat_ms;

    int max_heartbeat_ms = 1000*60*5;

    // Heartbeats are only enabled for 5 minutes after the
    // device boots up.
    if( millis() < max_heartbeat_ms ){
        if( sample_delta >= wait_ms){
            b->prev_heartbeat_ms = millis();
            return 1;
        }
        else{
            return 0;
        }
    }
}

static void ga_board_heartbeat_tx(struct ga_board* b){
    uint8_t payload[_GA_DEV_XBEE_BUFSIZE_];
    struct ga_heartbeat_packet hb_packet;

    hb_packet.schema = 5;
    hb_packet.uptime_ms = millis();
    hb_packet.batt_mv = ga_dev_batt_read();
    hb_packet.node_addr = ga_dev_eeprom_naddr_read();

    int schema_len = sizeof(hb_packet);

    Serial.println("TX Heartbeat Start");

    // We need to copy our struct data over to a byte array
    // to get a consistent size for sending over xbee.
    // Raw structs have alignment bytes that are in-between the
    // data bytes.
    memset(payload, '\0', sizeof(payload));
    memcpy(payload, &(hb_packet), schema_len);
    ga_dev_xbee_write(payload, schema_len);

    Serial.println("TX Heartbeat End");
}

static void ga_board_tx(struct ga_board* b){
    uint8_t payload[_GA_DEV_XBEE_BUFSIZE_];
    int schema_len = sizeof(b->data_packet);

    Serial.println("Sample TX Start");

    // We need to copy our struct data over to a byte array
    // to get a consistent size for sending over xbee.
    // Raw structs have alignment bytes that are in-between the
    // data bytes.
    memset(payload, '\0', sizeof(payload));
    memcpy(payload, &(b->data_packet), schema_len);
    ga_dev_xbee_write(payload, schema_len);

    // Reset the board sample count so that
    // goes through the sample loop again.
    b->sample_count = 0;

    Serial.println("Sample TX End");
}

static void ga_board_soft_rst(){
    asm volatile ("jmp 0");
}
