#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <CANCommunication.h>

#include "MPU9250.h"

// NeoPixel
#define PIN 17
#define NUM_PIXELS 100

MPU9250 mpu;
Adafruit_NeoPixel LEDs(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

long currentMillis = 0;

void setup() {
  Serial.begin(115200);
  //while (!Serial) delay(10);
  Wire.begin();

  setupCANCommunication();
  mpu.setup(0x68);
  mpu.calibrateAccelGyro();
  mpu.calibrateMag();

  LEDs.begin();
  LEDs.clear();
  LEDs.setBrightness(40);
}

void print_roll_pitch_yaw() {
  Serial.print("Yaw, Pitch, Roll: ");
  Serial.print(mpu.getYaw(), 2);
  Serial.print(", ");
  Serial.print(mpu.getPitch(), 2);
  Serial.print(", ");
  Serial.println(mpu.getRoll(), 2);
}

void loop() {
  currentMillis = millis();
  loopCANCommunication(currentMillis);

  for (int i = 0; i < NUM_PIXELS; i++) {
    // Set color of individual LED
    LEDs.setPixelColor(i, LEDs.Color(255 - (2 * i), 150, i * 2));
    // Write to hardware, else nothing would show
    LEDs.show();
    delay(20);
  }
  for (int i = 0; i < NUM_PIXELS; i++) {
    // Set color of individual LED
    LEDs.setPixelColor(i, LEDs.Color(0, 0, 0));
    // Write to hardware, else nothing would show
    LEDs.show();
    delay(20);
  }

  if (packetWaiting) {
    // ... new data arrived
    if (r_c1.x == 1) {
      // snake.up()
    } else if (r_c1.x == 2) {
      // snake.down()
    } else if (r_c1.x == 3) {
      // snake.left()
    } else if (r_c1.x == 4) {
      // snake.right()
    }

    packetWaiting = false;  // don't touch - reset and wait for new message
  }

  // Send data to CAN bus
  mpu.update();
  print_roll_pitch_yaw();
  w_c1.x = mpu.getRoll();
  w_c1.y = mpu.getPitch();
  w_c1.z = mpu.getYaw();
  w_c2.x = mpu.getAccX();
  w_c2.y = mpu.getAccY();
  w_c2.z = mpu.getAccZ();
}