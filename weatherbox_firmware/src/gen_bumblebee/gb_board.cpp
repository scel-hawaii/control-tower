/*******************************
 *
 * File: gb_board.cpp
 *
 * Contains definitions for board initialization, PlatformIO POST
 * commands, and sampling sensors.
 *
 * ****************************/

#include "gb_board.h"

static void gb_board_print_build_opts();
static void gb_board_setup(struct gb_board* b);
static void gb_board_post();

static void gb_board_run_cmd(struct gb_board* b);
static int gb_board_ready_run_cmd(struct gb_board* b);

static void gb_board_sample(struct gb_board* b);
static int gb_board_ready_sample(struct gb_board* b);

static void gb_board_tx(struct gb_board* b);
static int gb_board_ready_tx(struct gb_board* b);

static int gb_board_ready_heartbeat_tx(struct gb_board* b);
static void gb_board_heartbeat_tx(struct gb_board* b);

/******************************
 *
 * Name:        gb_board_init
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gb_board
 * Description: Initialize Apple board
 *
 ******************************/

void gb_board_init(gb_board *b){
    // Link functions to make them accessable
    b->print_build_opts = &gb_board_print_build_opts;
    b->setup = &gb_board_setup;
    b->post = &gb_board_post;

    // Sample and TX module
    b->tx = &gb_board_tx;
    b->ready_tx = &gb_board_ready_tx;
    b->sample = &gb_board_sample;
    b->ready_sample = &gb_board_ready_sample;

    // CMD Parsing Module
    b->run_cmd = &gb_board_run_cmd;
    b->ready_run_cmd = &gb_board_ready_run_cmd;

    // Heartbeat Module
    b->ready_heartbeat_tx = &gb_board_ready_heartbeat_tx;
    b->heartbeat_tx = &gb_board_heartbeat_tx;

    // State Variables
    b->sample_count = 0;
    b->node_address = 0;
    b->prev_sample_ms = 0;

    // Initialize the packet
    b->data_packet.schema = 1;
    b->data_packet.node_address = 0;
    b->data_packet.uptime_milliseconds = 0;
    b->data_packet.battery_millivolts = 0;
    b->data_packet.panel_millivolts = 0;
    b->data_packet.bme280_pressure_pascals = 0;
    b->data_packet.bme280_temperature_kelvin = 0;
    b->data_packet.bme280_humidity_percent = 0;
    b->data_packet.sp212_irradiance_watts_per_square_meter = 0;
}

/******************************
 *
 * Name:        gb_board_print_build_opts
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize board generation and baudrate
 *
 ******************************/

static void gb_board_print_build_opts()
{
    Serial.begin(9600);
    Serial.println(F("Board Opts"));
    Serial.println(F("Gen: apple23"));
}

/******************************
 *
 * Name:        gb_board_setup
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gb_board
 * Description: Enable sensor pin, initialize sensors,
 *              obtain node address from eeprom
 *
 ******************************/

static void gb_board_setup(struct gb_board* b){
    Serial.begin(9600);
    Serial.println(F("Board Setup Start"));

    // Open Devices
    gb_dev_digi_xbee_open();
    gb_dev_apogee_SP212_irradiance_open();
    gb_dev_battery_open();
    gb_dev_solar_panel_open();
    gb_dev_eeprom_node_address_open();
    gb_dev_adafruit_BME280_sensor_open();

    // load the address from the EEPROM into memory
    b->node_address = gb_dev_eeprom_node_address_read();

    delay(100);
    Serial.println(F("Board Setup Done"));
}

/******************************
 *
 * Name:        gb_board_post
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Power on self test when board initially starts
 *              and poll each sensor. Also used to check
 *              sensor values on serial monitor.
 *
 ******************************/

static void gb_board_post(){
    Serial.println(F("POST Begin"));

    // Display node addr
    Serial.print(F("[P] node addr: "));
    Serial.println((int) gb_dev_eeprom_node_address_read());

    // Check BME280 Humidity
    uint16_t BME280_humidity_val = gb_dev_adafruit_BME280_humidity_read();
    Serial.print(F("[P] BME280 Humidity value: "));
    Serial.print(BME280_humidity_val);
    Serial.println("\%");

    if(BME280_humidity_val < 0){
        Serial.println(F("[P] \tError: Humidity out of range"));
    }

    // Check BME280 Pressure
    int32_t BME280_pressure_val = gb_dev_adafruit_BME280_pressure_read();
    Serial.print(F("[P] BME280 Pressure value: "));
    Serial.print(BME280_pressure_val);
    Serial.println(" Pa");

    if(BME280_pressure_val < 80000){
        Serial.println(F("[P] \tError: Pressure out of range"));
    }

    // Check BME280 Temperature
    uint16_t BME280_temperature_val = gb_dev_adafruit_BME280_temperature_read();
    Serial.print(F("[P] BME280 Temperature value: "));
    Serial.print(BME280_temperature_val);
    Serial.println(F(" K"));

    if(BME280_temperature_val < 0){
        Serial.println(F("[P] \tError: Temperature out of range"));
    }

    // Check apogee_sp212
    int apogee_sp212_val = gb_dev_apogee_SP212_irradiance_read();
    Serial.print(F("[P] apogee_SP212 solar irradiance value: "));
    Serial.print(apogee_sp212_val);
    Serial.println(" mV");

    if(apogee_sp212_val < 0){
        Serial.println(F("[P] \tError: apogee solar irradiance out of range"));
    }

    // Check batt
    int batt_val = gb_dev_battery_read();
    Serial.print(F("[P] battery value: "));
    Serial.print(batt_val);
    Serial.println(" mV");

    if(batt_val < 0){
        Serial.println(F("[P] \tError: battery out of range"));
    }

    // check panel sensor value
    int spanel_val = gb_dev_solar_panel_read();
    Serial.print(F("[P] solar panel value: "));
    Serial.print(spanel_val);
    Serial.println(F(" mV"));

    if(spanel_val < 100){
        Serial.println(F("[P] \tERROR: solar panel value out of range"));
    }

    Serial.println(F("POST End"));

}

/******************************
 *
 * Name:        gb_board_sample
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gb-board
 * Description: Sample each sensor and store into data packet
 *
 ******************************/

static void gb_board_sample(struct gb_board* b){
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.println(F("Sample Start"));
    // Disabled this for apple deployment on 2016-10-06 with T=30s
    // Serial.println(b->sample_count);

    struct gb_packet* data_packet = &(b->data_packet);
    data_packet->uptime_milliseconds                     = millis();
    data_packet->battery_millivolts                      = gb_dev_battery_read();
    data_packet->panel_millivolts                        = gb_dev_solar_panel_read();
    data_packet->bme280_pressure_pascals                 = gb_dev_adafruit_BME280_pressure_read();
    data_packet->bme280_temperature_kelvin               = gb_dev_adafruit_BME280_temperature_read();
    data_packet->bme280_humidity_percent                 = gb_dev_adafruit_BME280_humidity_read();
    data_packet->sp212_irradiance_watts_per_square_meter = gb_dev_apogee_SP212_irradiance_read();
    data_packet->node_address                            = b->node_address;

    Serial.println(F("Sample End"));
    b->sample_count = 0;

    gb_board_tx(b);

    // Disabled this for apple deployment on 2016-10-06 with T=30s
    // b->sample_count++;
}

/******************************
 *
 * Name:        gb_board_ready_tx
 * Returns:     Integer indicating if ready to transmit
 * Parameter:   Function pointer to struct gb-board
 * Description: Checks to see if the board is ready
 *              transmit
 *
 ******************************/

static int gb_board_ready_tx(struct gb_board* b){
    // Disabled this for apple deployment on 2016-10-06 with T=30s
    /*
    const int max_samples = 20;
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
 * Name:        gb_board_ready_sample
 * Returns:     Integer indicating if ready to sample
 * Parameter:   Function pointer to struct gb-board
 * Description: Waits 30 seconds between sampling sensors
 *              and returns a 1 after thirty seconds. This
 *              is used in place of a delay because delay
 *              will block all other operations
 *
 ******************************/

static int gb_board_ready_sample(struct gb_board* b){
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
 * Name:        gb_board_ready_run_cmd
 * Returns:     Number of bytes available to read
 * Parameter:   Function pointer to struct gb-board
 * Description: Get the number of bytes avaiable for reading from the serial port
 *
 ******************************/

static int gb_board_ready_run_cmd(struct gb_board* b){
    return Serial.available();
}

/******************************
 *
 * Name:        gb_board_run_cmd
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gb-board
 * Description: Poll sensors in CMD mode in serial monitor
 *
 ******************************/

static void gb_board_run_cmd(struct gb_board* b){
    Serial.println(F("Enter CMD Mode"));
    while(Serial.read() != '\n');
    while(1){
        if(Serial.available()){
            char input = Serial.read();
            Serial.print(F("GOT A CMD: "));
            Serial.println(input);
            while(Serial.read() != '\n');
            if(input == 'E') {
                Serial.println(F("Leaving CMD mode"));
                break;
            }
            else{
                switch(input){
                    case 'T':
                        Serial.println(F("CMD Mode cmd"));
                        break;
                    case 'P':
                        Serial.println(F("Running POST"));
                        b->post();
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

/******************************
 *
 * Name:        gb_board_ready_heartbeat_tx
 * Returns:     Integer indicating if ready to transmit
 * Parameter:   Function pointer to struct gb-board
 * Description: Waits 3 seconds between sampling sensors
 *              and returns a 1 after three seconds. This
 *              is used in place of a delay because delay
 *              will block all other operations
 *
 ******************************/

static int gb_board_ready_heartbeat_tx(struct gb_board* b){
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

/******************************
 *
 * Name:        gb_board_heartbeat_tx
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gb-board
 * Description: Transmits heartbeat packet
 *
 ******************************/

static void gb_board_heartbeat_tx(struct gb_board* b){
    uint8_t payload[_GB_DEV_DIGI_XBEE_BUFSIZE_];
    struct gb_heartbeat_packet hb_packet;

    hb_packet.schema = 0;
    hb_packet.uptime_milliseconds = millis();
    hb_packet.battery_millivolts = gb_dev_battery_read();
    hb_packet.node_address = gb_dev_eeprom_node_address_read();

    int schema_len = sizeof(hb_packet);

    Serial.println(F("TX Heartbeat Start"));

    // We need to copy our struct data over to a byte array
    // to get a consistent size for sending over xbee.
    // Raw structs have alignment bytes that are in-between the
    // data bytes.
    memset(payload, '\0', sizeof(payload));
    memcpy(payload, &(hb_packet), schema_len);
    gb_dev_digi_xbee_write(payload, schema_len);

    Serial.println(F("TX Heartbeat End"));
}

/******************************
 *
 * Name:        gb_board_tx
 * Returns:     Nothing
 * Parameter:   Function pointer to struct gb-board
 * Description: Transmits sensor packet
 *
 ******************************/

static void gb_board_tx(struct gb_board* b){
    uint8_t payload[_GB_DEV_DIGI_XBEE_BUFSIZE_];
    int schema_len = sizeof(b->data_packet);

    Serial.println(F("Sample TX Start"));

    // We need to copy our struct data over to a byte array
    // to get a consistent size for sending over xbee.
    // Raw structs have alignment bytes that are in-between the
    // data bytes.
    memset(payload, '\0', sizeof(payload));
    memcpy(payload, &(b->data_packet), schema_len);
    gb_dev_digi_xbee_write(payload, schema_len);

    // Reset the board sample count so that
    // goes through the sample loop agbin.
    b->sample_count = 0;

    Serial.println(F("Sample TX End"));
}

static void gb_board_soft_rst(){
    asm volatile ("jmp 0");
}
