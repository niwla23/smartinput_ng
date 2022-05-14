#include <Arduino.h>
#include <FastLED.h>

const int16_t numPixels = 4;
const EOrder pixelsType = BRG;
const uint8_t pixelsPin = D5;

CRGB pixels[numPixels];

void ledSetup() {
    FastLED.addLeds<WS2811, pixelsPin, pixelsType>(pixels, numPixels);
    FastLED.setCorrection(CRGB(255, 160, 240));
    Serial.setTimeout(100);  // this makes sure ledLoop is not blocking the main loop for too long
}
// 0 = red
// 1 = green
// 2 = blue
// 3 = control byte
enum context_options {
    RED,
    GREEN,
    BLUE,
    CONTROL
};

// defines the current context of the value being read.
int valueContext = RED;
size_t currentPixel = 0;
uint8_t currentColor[3] = {};

void ledLoop() {
    while (Serial.available()) {
        int value = Serial.read();

        if (valueContext == CONTROL) {
            pixels[currentPixel] = CRGB(currentColor[RED], currentColor[GREEN], currentColor[BLUE]);

            valueContext = RED;
            currentPixel++;

            if (value == 1) {
                FastLED.show();
                currentPixel = 0;
            }

        } else {
            currentColor[valueContext] = value;
            valueContext++;
        }
    }
}