#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <CANCommunication.h>

#include "snake.h"

// begin - LED
#include <Adafruit_NeoPixel.h>

#include "MPU9250.h"
#define PIN 17  // For microBUS 1
// #define PIN 13 // For microBUS 2
#define NUM_PIXELS 100
MPU9250 mpu;
Adafruit_NeoPixel LEDs(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
// end - LED
long currentMillis = 0;
Game game;
Snake snake = Snake(game);
int matrix[101] = {0};

void print_roll_pitch_yaw() {
  Serial.print("Yaw, Pitch, Roll: ");
  Serial.print(mpu.getYaw(), 2);
  Serial.print(", ");
  Serial.print(mpu.getPitch(), 2);
  Serial.print(", ");
  Serial.println(mpu.getRoll(), 2);
}

int* get_color(int c) {
  switch (c) {
    case 1:;
      break;
    case 2:
      return new int[3]{0, 255, 255};
      break;
    case 3:
      return new int[3]{0, 255, 0};
      break;
    default:
      return new int[3]{0, 0, 0};
      break;
  }
}

void setup() {
  Serial.begin(115200);
  // while (!Serial) delay(10);
  Wire.begin();

  setupCANCommunication();

  mpu.setup(0x68);
  mpu.calibrateAccelGyro();
  mpu.calibrateMag();

  // Start LEDs
  LEDs.begin();
  // Clear all LEDs
  LEDs.clear();
  // Set brightness of all LEDs. [0, 255]
  LEDs.setBrightness(40);
}

int x_y_to_matrix(int x, int y) { return (y - 1) * 10 + x; }

void loop() {
  currentMillis = millis();
  loopCANCommunication(currentMillis);

  Position_Vector apples = game.getApples();
  //   Position_Vector snake = snake.getBody();

  for (Position p : apples) {
    matrix[x_y_to_matrix(p.x, p.y)] = 1;
  }

  // head other color
  //   matrix[x_y_to_matrix(snake[0].x, snake[0].y)] = 2;
  //   for (i = 1; i < snake.size(); i++) {
  //     matrix[x_y_to_matrix(p.x, p.y)] = 3;
  //   }

  for (int i = 1; i < NUM_PIXELS + 1; i++) {
    int color[3] = {0, 255, 0}; //get_color(matrix[i]);
    LEDs.setPixelColor(i, LEDs.Color(color[0], color[1], color[2]));
  }
  LEDs.show();

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
