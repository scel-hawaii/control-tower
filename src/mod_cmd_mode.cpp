#include "mod_cmd_mode.h"

void cmd_mode_check(){
#ifdef APPLE
    if(Serial.available()){
        Serial.println("Entered Command Mode");
        while(Serial.read() != '\n');
        while(1){
            if(Serial.available()){
                char input = Serial.read();
                Serial.print("GOT A COMMAND: ");
                Serial.println(input);
                while(Serial.read() != '\n');
                if(input == 'E') {
                    break;
                }
                else{
                    run_command(input);
                }
            }
        }
    }
#endif
}

static void run_command(char command){
#ifdef APPLE
    switch(command){
        case 'T':
            Serial.println("Stub Command Mode Command");
            break;
        default:
            break;
    }
#endif
}

