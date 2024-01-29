#include <Arduino.h>
#include <CANCommunication.h>

#include "snake.h"

// begin - LED
#include <Adafruit_NeoPixel.h>
#define PIN 17 // For microBUS 1
// #define PIN 13 // For microBUS 2
#define NUM_PIXELS 100
Adafruit_NeoPixel LEDs(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
// end - LED
long currentMillis = 0;

void setup() {
  snake Snake();

  Serial.begin(115200);
  //while (!Serial) delay(10);
  setupCANCommunication();

  // Start LEDs
  LEDs.begin();
  // Clear all LEDs
  LEDs.clear();
  // Set brightness of all LEDs. [0, 255]
  LEDs.setBrightness(40);
}

void loop() {
  currentMillis = millis();
  loopCANCommunication(currentMillis);

  // replace ths contents of the following if statement
  // with your incoming coordinates update functionality
  if (packetWaiting) {
    w_c1.x = r_c1.x + 1;
    w_c1.y = r_c1.y + 1;
    w_c1.z = r_c1.z + 1;
    w_c2.x = r_c2.x + 1;
    w_c2.y = r_c2.y + 1;
    w_c2.z = r_c2.z + 1;
    packetWaiting = false;
  }

  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;

  




  // put your code to update the outgoing coordinates
  // here
}