# 1 "C:\\Users\\ryans\\AppData\\Local\\Temp\\tmplztn7boh"
#include <Arduino.h>
# 1 "C:/Users/ryans/Documents/GitHub/WLED-Dog-Collar-Firmware/wled00/wled00.ino"
# 13 "C:/Users/ryans/Documents/GitHub/WLED-Dog-Collar-Firmware/wled00/wled00.ino"
#include "wled.h"
void setup();
void loop();
#line 15 "C:/Users/ryans/Documents/GitHub/WLED-Dog-Collar-Firmware/wled00/wled00.ino"
void setup() {
  WLED::instance().setup();
}

void loop() {
  WLED::instance().loop();
}