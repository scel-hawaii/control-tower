#include "log.h"
void print_log(const char str[]){
#ifdef DEBUG
    Serial.print("[");
    Serial.print(millis());
    Serial.print("]");
    Serial.print("   ");
    Serial.println(str);
#endif
}
