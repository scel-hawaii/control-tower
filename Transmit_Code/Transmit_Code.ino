/*
 * Tranmissiion Test
*/

/* Program Libraries */
#include "transmit.h"
#include "schema.h"
#include "packet_binary.h"
#include "sensors.h"
#include <overflow_checker.h>

/* Arduino Libraries */
#include <XBee.h>
#include <SHT1x.h>
#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <Adafruit_BMP085.h>

/* Macros */
#define MAX_SIZE 200

/* Global Variable for Packet (BAD FIND ALTERNATIVE) */
//uint8_t packet[MAX_SIZE];

void setup(){
    Serial.begin(9600);
//    Packet_Transmit(packet);

    /* Packet Binary Testing */
    schema_3 packet;

    clear_packet();
    packet.schema = 3;
}

void loop(){
//    Packet_Transmit(packet);
//    Serial.print("Packet Transmitted.\n");
//    delay(5000);

    samplePacketBinary();
    Serial.print("Packet sampled.\n");
    delay(5000);
}
