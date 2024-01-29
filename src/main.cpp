#include <Arduino.h>
#include <CANCommunication.h>

#include "MPU9250.h"

MPU9250 mpu;

long currentMillis = 0;

void setup() {
  Serial.begin(115200);
  //while (!Serial) delay(10);
  Wire.begin();

  setupCANCommunication();
  mpu.setup(0x68);
  mpu.calibrateAccelGyro();
  mpu.calibrateMag();
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

  if (packetWaiting) {
    // ... new data arrived
    packetWaiting = false;  // don't touch
  }

  mpu.update();
  print_roll_pitch_yaw();
  w_c1.x = mpu.getRoll();
  w_c1.y = mpu.getPitch();
  w_c1.z = mpu.getYaw();
  w_c2.x = mpu.getAccX();
  w_c2.y = mpu.getAccY();
  w_c2.z = mpu.getAccZ();
  // put your code to update the outgoing coordinates
  // here
}