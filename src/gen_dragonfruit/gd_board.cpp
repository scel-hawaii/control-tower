#include "gd_board.h"

static void gd_board_print_build_opts();
static void gd_board_setup(struct gd_board* b);
static void gd_board_post();

static void gd_board_run_cmd(struct gd_board* b);
static int gd_board_ready_run_cmd(struct gd_board* b);

static void gd_board_sample(struct gd_board* b);
static int gd_board_ready_sample(struct gd_board* b);

static void gd_board_tx(struct gd_board* b);
static int gd_board_ready_tx(struct gd_board* b);

static int gd_board_ready_heartbeat_tx(struct gd_board* b);
static void gd_board_heartbeat_tx(struct gd_board* b);

void gd_board_init(gd_board *b){
    // Link functions to make them accessable
    b->print_build_opts = &gd_board_print_build_opts;
    b->setup = &gd_board_setup;
    b->post = &gd_board_post;

    // Sample and TX module
    b->tx = &gd_board_tx;
    b->ready_tx = &gd_board_ready_tx;
    b->sample = &gd_board_sample;
    b->ready_sample = &gd_board_ready_sample;

    // CMD Parsing Module
    b->run_cmd = &gd_board_run_cmd;
    b->ready_run_cmd = &gd_board_ready_run_cmd;

    // Heartbeat Module
    b->ready_heartbeat_tx = &gd_board_ready_heartbeat_tx;
    b->heartbeat_tx = &gd_board_heartbeat_tx;

    // State Variables
    b->sample_count = 0;
    b->node_addr = 0;
    b->prev_sample_ms = 0;

    // Initialize the packet
    b->data_packet.schema = 3;
    b->data_packet.node_addr = 0;
    b->data_packet.uptime_ms = 0;
    b->data_packet.batt_mv = 0;
    b->data_packet.panel_mv = 0;
    b->data_packet.bmp085_press_pa = 0;
    b->data_packet.bmp085_temp_decic = 0;
    b->data_packet.humidity_centi_pct = 0;
    b->data_packet.apogee_w_m2 = 0;
}

static void gd_board_print_build_opts()
{
    Serial.begin(9600);
    Serial.println(F("Board Opts"));
    Serial.println(F("Gen: apple23"));
}

static void gd_board_setup(struct gd_board* b){
    Serial.begin(9600);
    Serial.println(F("Board Setup Start"));

    // Open Devices
    gd_dev_xbee_open();
    gd_dev_sht1x_open();
    gd_dev_bmp085_open();
    gd_dev_apogee_sp212_open();
    gd_dev_batt_open();
    gd_dev_spanel_open();
    gd_dev_eeprom_naddr_open();

    // load the address from the hardware
    b->node_addr = gd_dev_eeprom_naddr_read();

    delay(100);
    Serial.println(F("Board Setup Done"));
}

// power on self test
static void gd_board_post(){
    Serial.println(F("POST Begin"));

    // Display node addr
    Serial.print(F("[P] node addr: "));
    Serial.println((int) gd_dev_eeprom_naddr_read());

    // Check sht1x
    int sht1x_val = gd_dev_sht1x_read();
    Serial.print(F("[P] sht1x value: "));
    Serial.print(sht1x_val);
    Serial.println("\%");

    if(sht1x_val < 0){
        Serial.println(F("[P] \tError: Humidity out of range"));
    }

    // Check BMP085
    int32_t bmp085_val = gd_dev_bmp085_read();
    Serial.print(F("[P] bmp085 value: "));
    Serial.print(bmp085_val/10);
    Serial.print(F("."));
    Serial.print((bmp085_val-bmp085_val/10)/1000);
    Serial.println(" mb");

    if(bmp085_val < 80000){
        Serial.println(F("[P] \tError: bmp085 pressure out of range"));
    }

    // Check BMP085 temperature
    uint16_t bmp085_temp = gd_dev_bmp085_read_temp();
    Serial.print(F("[P] bmp085 temp: "));
    Serial.print(bmp085_temp/10);
    Serial.print(".");
    Serial.print((bmp085_temp-bmp085_temp/10)/10);
    Serial.println(F(" celsius"));

    if(bmp085_temp < 0){
        Serial.println(F("[P] Error: bmp085 temperature out of range"));
    }

    // Check apogee_sp212
    int apogee_sp212_val = gd_dev_apogee_sp212_read();
    Serial.print(F("[P] apogee_sp212 solar irr value: "));
    Serial.print(apogee_sp212_val*(5000/1023));
    Serial.println(" mV");

    if(apogee_sp212_val < 0){
        Serial.println(F("[P] \tError: apogee solar irr out of range"));
    }

    // Check batt
    int batt_val = gd_dev_batt_read();
    Serial.print(F("[P] batt value: "));
    Serial.print(batt_val*(5000/1023));
    Serial.println(" mV");

    if(batt_val < 0){
        Serial.println(F("[P] Error: batt out of range"));
    }

    // check panel sensor value
    int spanel_val = gd_dev_spanel_read();
    Serial.print(F("[P] spanel value: "));
    Serial.print(2*spanel_val*(5000/1023)+70);
    Serial.println(F(" mV"));

    if(spanel_val < 100){
        Serial.println(F("[P] \tERROR: spanel value out of range"));
    }

    Serial.println(F("POST End"));

}

static void gd_board_sample(struct gd_board* b){
    Serial.println(F("Sample Start"));
    Serial.println(b->sample_count);

    struct gd_packet* data_packet = &(b->data_packet);
    data_packet->uptime_ms           = millis();
    data_packet->batt_mv             = gd_dev_batt_read();
    data_packet->panel_mv            = gd_dev_spanel_read();
    data_packet->bmp085_press_pa     = gd_dev_bmp085_read();
    data_packet->bmp085_temp_decic   = gd_dev_bmp085_read_temp();
    data_packet->humidity_centi_pct  = gd_dev_sht1x_read();
    data_packet->apogee_w_m2         = gd_dev_apogee_sp212_read();

    Serial.println(F("Sample End"));
    b->sample_count++;
}

static int gd_board_ready_tx(struct gd_board* b){
    const int max_samples = 20;
    if(b->sample_count > max_samples-1){
        return 1;
    }
    else{
        return 0;
    }
}

static int gd_board_ready_sample(struct gd_board* b){
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

static int gd_board_ready_run_cmd(struct gd_board* b){
    return Serial.available();
}

static void gd_board_run_cmd(struct gd_board* b){
    Serial.println(F("Enter CMD Mode"));
    while(Serial.read() != '\n');
    while(1){
        if(Serial.available()){
            char input = Serial.read();
            Serial.print(F("GOT A CMD: "));
            Serial.println(input);
            while(Serial.read() != '\n');
            if(input == 'E') {
                break;
            }
            else{
                switch(input){
                    case 'T':
                        Serial.println(F("CMD Mode cmd"));
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

static int gd_board_ready_heartbeat_tx(struct gd_board* b){
    const int wait_ms = 3000;
    int sample_delta = millis() - b->prev_heartbeat_ms;

    unsigned long max_heartbeat_ms = (unsigned long) 1000*69*5;

    int heartbeat_enable = 1;

    #ifndef HB_FOREVER
    heartbeat_enable = millis() < max_heartbeat_ms;
    #endif

    // Heartbeats are only enabled for 5 minutes after the
    // device boots up.
    if( heartbeat_enable ){
        if( sample_delta >= wait_ms){
            b->prev_heartbeat_ms = millis();
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}

static void gd_board_heartbeat_tx(struct gd_board* b){
    uint8_t payload[_GD_DEV_XBEE_BUFSIZE_];
    struct gd_heartbeat_packet hb_packet;

    hb_packet.schema = 0;
    hb_packet.uptime_ms = millis();
    hb_packet.batt_mv = gd_dev_batt_read();
    hb_packet.node_addr = gd_dev_eeprom_naddr_read();

    int schema_len = sizeof(hb_packet);

    Serial.println(F("TX Heartbeat Start"));

    // We need to copy our struct data over to a byte array
    // to get a consistent size for sending over xbee.
    // Raw structs have alignment bytes that are in-between the
    // data bytes.
    memset(payload, '\0', sizeof(payload));
    memcpy(payload, &(hb_packet), schema_len);
    gd_dev_xbee_write(payload, schema_len);

    Serial.println(F("TX Heartbeat End"));
}

static void gd_board_tx(struct gd_board* b){
    uint8_t payload[_GD_DEV_XBEE_BUFSIZE_];
    int schema_len = sizeof(b->data_packet);

    Serial.println(F("Sample TX Start"));

    // We need to copy our struct data over to a byte array
    // to get a consistent size for sending over xbee.
    // Raw structs have alignment bytes that are in-between the
    // data bytes.
    memset(payload, '\0', sizeof(payload));
    memcpy(payload, &(b->data_packet), schema_len);
    gd_dev_xbee_write(payload, schema_len);

    // Reset the board sample count so that
    // goes through the sample loop agdin.
    b->sample_count = 0;

    Serial.println(F("Sample TX End"));
}

static void gd_board_soft_rst(){
    asm volatile ("jmp 0");
}
