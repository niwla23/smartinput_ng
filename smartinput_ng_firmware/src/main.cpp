#include <Arduino.h>

constexpr int longPressTimeMs = 1500;
constexpr int numKeys = 3;
constexpr int keyPins[numKeys] = {3, 4, 5};    // GPIO pins used for switches
constexpr int inputType[numKeys] = {0, 1, 0};  // 0 for default-off, 1 for default-on

void setup() {
    for (size_t i = 0; i < numKeys; i++) {
        pinMode(keyPins[i], INPUT_PULLUP);
    }

    Serial.begin(9600);
}

enum eventType { press,
                 shortPress,
                 longPress,
                 release
};

// state of the keys. 0 means not pressed, otherwise the time of press in millis since startup is stored.
unsigned long keysPressedSince[numKeys] = {0};
bool keysTriggeredLongPress[numKeys] = {false};

void handleEvent(int key, eventType type) {
    if (type == press) {
        Serial.print("P");
    } else if (type == longPress) {
        Serial.print("L");
    } else if (type == shortPress) {
        Serial.print("S");
    } else if (type == release) {
        Serial.print('R');
    }
    Serial.print(":");
    Serial.println(key);
    Serial.flush();
}

void loop() {
    for (size_t i = 0; i < numKeys; i++) {
        unsigned long now = millis();

        int pin = keyPins[i];

        int read = digitalRead(pin);

        if (inputType[i] == 1) {  // invert read if we have a default-on switch
            read = 1 - read;
        }

        unsigned long lastState = keysPressedSince[i];

        if (lastState == 0) {   // last time button was not pressed
            if (read == LOW) {  // if button is pressed now
                keysPressedSince[i] = now;
                handleEvent(i, press);
            }
        } else {                 // last time button was pressed so we have the time of press start
            if (read == HIGH) {  // button is not pressed anymore, send release event
                keysPressedSince[i] = 0;
                if (!keysTriggeredLongPress[i]) { // if there was no long press, we are still in time for a short press, send event
                    handleEvent(i, shortPress);
                }
                keysTriggeredLongPress[i] = false;
                handleEvent(i, release);
            }
            if (read == LOW) {  // button was pressed last time AND is still pressed
                // threshold for long press reached and long press event has not been sent yet
                if ((now - lastState) > longPressTimeMs && !keysTriggeredLongPress[i]) {
                    keysTriggeredLongPress[i] = true;
                    handleEvent(i, longPress);
                }
            }
        }
    }
}