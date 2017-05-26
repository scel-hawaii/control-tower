/*******************************
 *
 * File: gc_board.cpp
 *
 * Contains definitions for board initialization, PlatformIO POST
 * commands, and sampling sensors.
 *
 * ****************************/

#include "gc_board.h"

static void gc_board_print_build_opts();
static void gc_board_setup(struct gc_board* b);
static void gc_board_post();

static void gc_board_run_cmd(struct gc_board* b);
static int gc_board_ready_run_cmd(struct gc_board* b);

static void gc_board_sample(struct gc_board* b);
static int gc_board_ready_sample(struct gc_board* b);

static void gc_board_tx(struct gc_board* b);
static int gc_board_ready_tx(struct gc_board* b);

static int gc_board_ready_heartbeat_tx(struct gc_board* b);
static void gc_board_heartbeat_tx(struct gc_board* b);

/******************************
 *
 * Name:        gc_board_init
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gc_board
 * Description: Initialize Cranberry board
 *
 ******************************/

void gc_board_init(gc_board *b){
    // Link functions to make them accessable
    b->print_build_opts = &gc_board_print_build_opts;
    b->setup = &gc_board_setup;
    b->post = &gc_board_post;

    // Sample and TX module
    b->tx = &gc_board_tx;
    b->ready_tx = &gc_board_ready_tx;
    b->sample = &gc_board_sample;
    b->ready_sample = &gc_board_ready_sample;

    // CMD Parsing Module
    b->run_cmd = &gc_board_run_cmd;
    b->ready_run_cmd = &gc_board_ready_run_cmd;

    // Heartbeat Module
    b->ready_heartbeat_tx = &gc_board_ready_heartbeat_tx;
    b->heartbeat_tx = &gc_board_heartbeat_tx;

    // State Variables
    b->sample_count = 0;
    b->node_address = 0;
    b->prev_sample_ms = 0;

    // Initialize the packet
    b->data_packet.schema = 2;
    b->data_packet.node_address = gc_dev_eeprom_node_address_read();
    b->data_packet.uptime_milliseconds = 0;
    b->data_packet.battery_millivolts = 0;
    b->data_packet.panel_millivolts = 0;
    b->data_packet.sp212_irradiance_watts_per_square_meter = 0;
    b->data_packet.hih6131_temperature_kelvin = 0;
    b->data_packet.hih6131_humidity_percent = 0;
    b->data_packet.mpl115a2t1_pressure_pascals = 0;
}

/******************************
 *
 * Name:        gc_board_print_build_opts
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize board generation and baudrate
 *
 ******************************/

static void gc_board_print_build_opts()
{
    Serial.begin(9600);
    Serial.println(F("Board Opts"));
    Serial.println(F("Gen: cranberry"));
}

/******************************
 *
 * Name:        gc_board_setup
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gc_board
 * Description: Enable sensor pin, initialize sensors,
 *              obtain node address from eeprom
 *
 ******************************/

static void gc_board_setup(struct gc_board* b){
    Serial.begin(9600);
    Serial.println(F("Board Setup Start"));

    // Open Devices
    digitalWrite(_PIN_SEN_EN, HIGH);
    gc_dev_digi_xbee_open();
    gc_dev_apogee_SP212_irradiance_open();
    gc_dev_battery_open();
    gc_dev_solar_panel_open();
    gc_dev_eeprom_node_address_open();
    gc_dev_honeywell_HIH6131_humidity_open();
    gc_dev_honeywell_HIH6131_temperature_open();
    gc_dev_adafruit_MPL115A2_pressure_open();

    // Load the address from the hardware
    b->node_address = gc_dev_eeprom_node_address_read();

    delay(100);
    Serial.println(F("Board Setup Done"));
}

/******************************
 *
 * Name:        gc_board_post
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Power on self test when board initially starts
 *              and poll each sensor. Also used to check
 *              sensor values on serial monitor.
 *
 ******************************/

static void gc_board_post(){
    Serial.println(F("POST Begin"));

    // Display node addr
    gc_dev_eeprom_node_address_test();

    // Check hih6131 temperature
    gc_dev_honeywell_HIH6131_temperature_centik_test();

    // Check hih6131 humidity
    gc_dev_honeywell_HIH6131_humidity_pct_test();

    // Check mpl115a2t1 pressure
    gc_dev_adafruit_MPL115A2_pressure_pa_test();

    // Check apogee_sp212
    gc_dev_apogee_SP212_irradiance_test();

    // Check battery voltage
    gc_dev_battery_test();

    // check panel sensor value
    gc_dev_solar_panel_test();

    Serial.println(F("POST End"));
}

/******************************
 *
 * Name:        gc_board_sample
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gc-board
 * Description: Sample each sensor and store into data packet
 *
 ******************************/

static void gc_board_sample(struct gc_board* b){
    Serial.print("[");
    Serial.print(millis());
    Serial.println("]");

    Serial.println(F("Sample Start"));

    //Disabled for Cranberry Deployment, T=30s
    //Serial.println(b->sample_count);

    struct gc_packet* data_packet = &(b->data_packet);
    data_packet->uptime_milliseconds                     = millis();
    data_packet->battery_millivolts                      = gc_dev_battery_read();
    data_packet->panel_millivolts                        = gc_dev_solar_panel_read();
    data_packet->sp212_irradiance_watts_per_square_meter = gc_dev_apogee_SP212_irradiance_read();
    data_packet->hih6131_temperature_kelvin              = gc_dev_honeywell_HIH6131_temperature_centik_read();
    data_packet->hih6131_humidity_percent                = gc_dev_honeywell_HIH6131_humidity_pct_read();
    data_packet->mpl115a2t1_pressure_pascals             = gc_dev_adafruit_MPL115A2_pressure_pa_read();

    Serial.println(F("Sample End"));
    b->sample_count = 0;

    //Disabled for Cranberry Deployment, T=30s
    //b->sample_count++;

    gc_board_tx(b);
}

/******************************
 *
 * Name:        gc_board_ready_tx
 * Returns:     Integer indicating if ready to transmit
 * Parameter:   Function pointer to struct gc-board
 * Description: Checks to see if the board is ready
 *              transmit
 *
 ******************************/

static int gc_board_ready_tx(struct gc_board* b){
    //Disabled for Cranberry Deployment, T=30s
/*    const int max_samples = 20;
    if(b->sample_count > max_samples-1){
        return 1;
    }
    else{
        return 0;
    }
*/
    return 0;
}

/******************************
 *
 * Name:        gc_board_ready_sample
 * Returns:     Integer indicating if ready to sample
 * Parameter:   Function pointer to struct gc-board
 * Description: Waits 30 seconds between sampling sensors
 *              and returns a 1 after thirty seconds. This
 *              is used in place of a delay because delay
 *              will block all other operations
 *
 ******************************/

static int gc_board_ready_sample(struct gc_board* b){
    const unsigned long wait_ms = 1000*30;
    const unsigned long sample_delta = millis() - b->prev_sample_ms;

    if( sample_delta >= wait_ms){
        b->prev_sample_ms = millis();
        return 1;
    }
    else{
        return 0;
    }
}

/******************************
 *
 * Name:        gc_board_ready_run_cmd
 * Returns:     Number of bytes available to read
 * Parameter:   Function pointer to struct gc-board
 * Description: Get the number of bytes avaiable for reading from the serial port
 *
 ******************************/

static int gc_board_ready_run_cmd(struct gc_board* b){
    return Serial.available();
}

/******************************
 *
 * Name:        gc_board_run_cmd
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gc-board
 * Description: Poll sensors in CMD mode in serial monitor
 *
 ******************************/

static void gc_board_run_cmd(struct gc_board* b){
    Serial.println(F("\nEnter CMD Mode"));
    Serial.println(F("[E] - Exit Command Mode"));
    Serial.println(F("[P] - Run Power On Self-Test"));
    Serial.println(F("[S] - Sensor Sampling Menu"));


    while(Serial.read() != '\n'); //In Arduino IDE, make sure line ending is \n
    while(1){
        if(Serial.available()){
            char input = Serial.read(), input2;

            Serial.print(F("GOT A CMD: "));
            Serial.println(input);
            while(Serial.read() != '\n');
            if(input == 'E') {
                Serial.println(F("Leaving CMD Mode"));
                break;
            }
            else{
                switch(input){
                    case 'P':
                        Serial.println(F("Running POST"));
                        b->post();
                        break;
                    case 'S':
                        Serial.println(F("\nSensor Sampling Menu"));
                        Serial.println(F("[1] - Node Address"));
                        Serial.println(F("[2] - HIH6131 Temperature (cK)"));
                        Serial.println(F("[3] - HIH6131 Humidity (\%)"));
                        Serial.println(F("[4] - MPL115A2 Pressure (Pa)"));
                        Serial.println(F("[5] - SP212 Solar Irradiance (mW)"));
                        Serial.println(F("[6] - Battery Voltage (mW)"));
                        Serial.println(F("[7] - Solar Panel Voltage (mW)"));
                        Serial.println(F("[E] - Exit to Main Menu"));

                        while(1){
                            if(Serial.available()){
                                input2 = Serial.read();
                                Serial.print(F("GOT A CMD: "));
                                Serial.println(input2);
                                while(Serial.read() != '\n');
                                    if(input2 == 'E'){
                                        Serial.println(F("Exiting to Main Menu"));
                                        break;
                                    }
                                    switch(input2){
                                        case '1':
                                            gc_dev_eeprom_node_address_test();
                                            break;
                                        case '2':
                                            gc_dev_honeywell_HIH6131_temperature_centik_test();
                                            break;
                                        case '3':
                                            gc_dev_honeywell_HIH6131_humidity_pct_test();
                                            break;
                                        case '4':
                                            gc_dev_adafruit_MPL115A2_pressure_pa_test();
                                            break;
                                        case '5':
                                            gc_dev_apogee_SP212_irradiance_test();
                                            break;
                                        case '6':
                                            gc_dev_battery_test();
                                            break;
                                        case '7':
                                            gc_dev_solar_panel_test();
                                            break;
                                        default:
                                            break;
                                  }
                              }
                          }
                    default:
                        break;
                }
            }
        }
    }
}

/******************************
 *
 * Name:        gc_board_run_cmd
 * Returns:     Integer indicating if ready to transmit
 * Parameter:   Function pointer to struct gc-board
 * Description: Waits 3 seconds between sampling sensors
 *              and returns a 1 after three seconds. This
 *              is used in place of a delay because delay
 *              will block all other operations
 *
 ******************************/

static int gc_board_ready_heartbeat_tx(struct gc_board* b){
    const int wait_ms = 3000;
    int sample_delta = millis() - b->prev_heartbeat_ms;

    unsigned long max_heartbeat_ms = (unsigned long) 1000*69*5;

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
    return 0;
}

/******************************
 *
 * Name:        gc_board_heartbeat_tx
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gc-board
 * Description: Transmits heartbeat packet
 *
 ******************************/

static void gc_board_heartbeat_tx(struct gc_board* b){
    uint8_t payload[_GC_DEV_DIGI_XBEE_BUFSIZE_];
    struct gc_heartbeat_packet hb_packet;

    hb_packet.schema = 0;
    hb_packet.uptime_milliseconds = millis();
    hb_packet.battery_millivolts = gc_dev_battery_read();
    hb_packet.node_address = gc_dev_eeprom_node_address_read();

    int schema_len = sizeof(hb_packet);

    Serial.println(F("TX Heartbeat Start"));

    // We need to copy our struct data over to a byte array
    // to get a consistent size for sending over xbee.
    // Raw structs have alignment bytes that are in-between the
    // data bytes.
    memset(payload, '\0', sizeof(payload));
    memcpy(payload, &(hb_packet), schema_len);
    gc_dev_digi_xbee_write(payload, schema_len);

    Serial.println(F("TX Heartbeat End"));
}

/******************************
 *
 * Name:        gc_board_tx
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gc-board
 * Description: Transmits sensor packet
 *
 ******************************/

static void gc_board_tx(struct gc_board* b){
    uint8_t payload[_GC_DEV_DIGI_XBEE_BUFSIZE_];
    int schema_len = sizeof(b->data_packet);

    Serial.println(F("Sample TX Start"));

    // We need to copy our struct data over to a byte array
    // to get a consistent size for sending over xbee.
    // Raw structs have alignment bytes that are in-between the
    // data bytes.
    memset(payload, '\0', sizeof(payload));
    memcpy(payload, &(b->data_packet), schema_len);
    gc_dev_digi_xbee_write(payload, schema_len);

    // Reset the board sample count so that
    // goes through the sample loop again.
    b->sample_count = 0;

    Serial.println(F("Sample TX End"));
}

static void gc_board_soft_rst(){
    asm volatile ("jmp 0");
}
