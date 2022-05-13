#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

Adafruit_NeoPixel pixels;

const int16_t numPixels = 4;
const uint16_t pixelsType = NEO_BRG + NEO_KHZ800;
const uint8_t pixelsPin = D5;

void ledSetup() {
    // gRedPin = redPin;
    // gGreenPin = greenPin;
    // gBluePin = bluePin;
    // pinMode(gRedPin, OUTPUT);
    // pinMode(gGreenPin, OUTPUT);
    // pinMode(gBluePin, OUTPUT);
    pixels = Adafruit_NeoPixel(numPixels, pixelsPin, pixelsType);
    pixels.begin();
    Serial.setTimeout(100);  // this makes sure ledLoop is not blocking the main loop for too long
}

void setColor(uint8_t red, uint8_t green, uint8_t blue) {
    // digitalWrite(gRedPin, red);
    // digitalWrite(gGreenPin, green);
    // digitalWrite(gBluePin, blue);
}

const int BUFFER_SIZE = 1;
char buf[BUFFER_SIZE];

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
int currentPixel = 0;
int currentColor[3] = {};

void ledLoop() {
    while (Serial.available()) {
        int value = Serial.read();

        if (valueContext == CONTROL) {
            valueContext = RED;
            if (value == 1) {
                pixels.show();
                currentPixel = 0;
            }
        } else if (valueContext == BLUE) {
            currentColor[valueContext] = value;
            pixels.setPixelColor(currentPixel, pixels.Color(currentColor[RED], currentColor[GREEN], currentColor[BLUE]));
            currentPixel++;
            valueContext = CONTROL;
        } else {
            currentColor[valueContext] = value;
            valueContext++;
        }
    }
}