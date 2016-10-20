/*
 *
 * burn_node_id.ino
 *
 * Writes the specified node id into the arduino EEProm
 *
 */

#include <EEPROM.h>
#define DEBUG

void setup() {
    Serial.begin(9600);
}
void loop(){
    unsigned int id = 0;
    char incomingByte[4];

    int rawString = 0;
    int number = 0;
    int i = 0;
    int invalid = 0;
    int done = 0;
    Serial.print("Current device's node id: ");
    Serial.println( (EEPROM.read(2) | (EEPROM.read(3)<<8)) );

    Serial.println("Please enter the node id to burn:");

    while(incomingByte[i] != '\n') {
        if(Serial.available() > 0){
            incomingByte[i] = Serial.read();
            #ifdef DEBUG
            Serial.print(i);
            Serial.print(" ");
            Serial.print("I recieved: ");
            Serial.println(incomingByte[i]);
            #endif
            if(i > 4){
                invalid = 1;
                break;
            }
            else if(i > 3 && (incomingByte[i] !='\n')){
                //Serial.println("Invalid input.");
                invalid = 1;
                break;
            }
            else if(incomingByte[i] == '\n') break;
            i++;
        }


    }
    if(invalid == 0){
        incomingByte[i] = '\0';
        number = atoi(incomingByte);
        Serial.print("You entered: ");
        Serial.println(number);
        Serial.print("Are you sure that you want to set this ");
        Serial.print("device to Node ID ");
        Serial.print(number);
        Serial.print(" (Y/N)?: ");
        Serial.println();

        while(done == 0){
            if(Serial.available() > 0){
                incomingByte[0] = Serial.read();
                if(incomingByte[0] == 'Y'){
                    uint8_t high;
                    uint8_t low;
                    int test;
                    high = (uint8_t)(number >> 8);
                    low = number & 0xff;
                    Serial.println(high, BIN);
                    Serial.println(low, BIN);

                    Serial.println("Burning Node ID to address 2 and 3");
                    EEPROM.write(2,low);
                    EEPROM.write(3,high);
                    Serial.println("Done");
                    Serial.println("Verify that the bytes are correct");
                    test = EEPROM.read(2) | (EEPROM.read(3)<<8);
                    Serial.print("Read node ID: ");
                    Serial.println(test);

                    done = 1;
                    break;
                }
                else if(incomingByte[0] == 'N'){
                    Serial.println("Cancel Burning");
                    done = 1;
                    break;
                }
            }
        }
    }
    else{
        #ifdef DEBUG
        Serial.println("Invalid input.");
        #endif
        while(Serial.available() > 0) Serial.read();
    }
    Serial.println("Finish");
    while(1);

}

void printIntro(){
    Serial.println("SCEL Weatherbox Node ID burn program loaded.");
    Serial.print("This program will write to the arduino EEPROM");
    Serial.print("which is a part of memory that is persistant through");
    Serial.print("Shutdowns. This means that we will be able to burn the");
    Serial.print("node IDs and read them at startup from each weatherbox.");
    Serial.println();
    Serial.println();
    Serial.print("**A word of caution**: the EEPROM memory has only");
    Serial.print("around 100,000 write/erase cycles, so be careful");
    Serial.print("about how often you write to them.");

    Serial.println();
    Serial.println();
}


