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

uint32_t ledBuffer[numPixels];
char messageBuffer[16] = {};
int currentPosition = 0;
int currentPixel = 0;
void ledLoop() {
    // pixels.setPixelColor(1, pixels.Color(0, 255, 0));
    // pixels.show();
    if (!Serial.available()) {
        return;
    }
    String received = Serial.readString();
    const char* received_c = received.c_str();

    for (int i = 0; i < received.length(); i++) {
        if (received_c[i] == '\n') {
            messageBuffer[currentPosition] = '\0';
            Serial.print("settning color to");
            int colorValue = atoi(messageBuffer);
            Serial.println(colorValue);
            Serial.print("pixel: ");
            Serial.println(currentPixel);
            ledBuffer[currentPixel] = colorValue;
            Serial.println("tf?");
            currentPixel++;
        } else if (received_c[i] == ';') {
            messageBuffer[currentPosition] = '\0';
            Serial.println("showing pixels, seperator received");
            for (size_t i = 0; i < numPixels; i++) {
                Serial.println(ledBuffer[i]);
                pixels.setPixelColor(i, ledBuffer[i]);
            }

            pixels.show();
            currentPosition = 0;
            currentPixel = 0;
            Serial.flush();
            continue;
        } else {
            Serial.println("received message, writing data to buffer");
            messageBuffer[currentPosition] = received_c[i];
        }
        currentPosition++;
    }
}