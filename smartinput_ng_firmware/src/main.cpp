#include <Keypad.h>

#include "led.hpp"

const byte ROWS = 4;  // four rows
const byte COLS = 3;  // three columns
char keys[ROWS][COLS] = {
    {'8', '4', '0'},
    {'9', '5', '1'},
    {'A', '6', '2'},
    {'B', '7', '3'}};

byte rowPins[ROWS] = {D1, D2, D3, D4};  // connect to the column pinouts of the kpd
byte colPins[COLS] = {D8, D7, D6};      // arduino libs are weird. won't work in normal odrder.
constexpr int longPressTimeMs = 1000;

unsigned long keysPressedSince[ROWS * COLS] = {0};
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

unsigned long loopCount;
unsigned long startTime;
String msg;

void setup() {
    Serial.begin(115200);
    kpd.setHoldTime(longPressTimeMs);
    loopCount = 0;
    startTime = millis();
    msg = "";
    ledSetup();
}

void loop() {
    
    ledLoop();

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys()) {
        for (int i = 0; i < LIST_MAX; i++)  // Scan active keys
        {
            if (kpd.key[i].stateChanged)  // Only execute for changed keys
            {
                switch (kpd.key[i].kstate) {
                    case PRESSED:
                        msg = "P";
                        keysPressedSince[kpd.key[i].kcode] = millis();
                        break;
                    case HOLD:
                        msg = "L";
                        break;
                    case RELEASED:
                        msg = "R";

                        // this is an extra event that is triggered after the key is released and was NOT pressed for > longPressTimeMs
                        if ((millis() - keysPressedSince[kpd.key[i].kcode]) < longPressTimeMs) {
                            Serial.print("S");
                            Serial.print(":");
                            Serial.println(kpd.key[i].kchar);
                        }
                        break;
                    case IDLE:
                        continue;
                }
                Serial.print(msg);
                Serial.print(":");
                Serial.println(kpd.key[i].kchar);
                Serial.flush();
            }
        }
    } 
}