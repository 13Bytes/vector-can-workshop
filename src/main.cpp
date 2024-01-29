#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <CANCommunication.h>
#include <math.h>

#include "MPU9250.h"
#include "game.h"
#include "snake.h"

// NeoPixel
#define PIN 17
#define NUM_PIXELS 100

MPU9250 mpu;
Adafruit_NeoPixel LEDs(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

long currentMillis = 0;

Game game;
Snake snake = Snake(&game);
int matrix[101] = {0};

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
int x_y_to_matrix(int x, int y) { return (y - 1) * 10 + x; }

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

  Position_Vector apples = game.getApples();
  Position_Vector snakePos = snake.getBody();

  for (Position p : apples) {
    matrix[x_y_to_matrix(p.x, p.y)] = 1;
  }

  // head other color
  matrix[x_y_to_matrix(snakePos[0].x, snakePos[0].y)] = 2;
  for (int i = 1; i < snakePos.size(); i++) {
    matrix[x_y_to_matrix(snakePos[i].x, snakePos[i].y)] = 3;
  }
  for (int i = 0; i < NUM_PIXELS + 1; i++) {
    int* color = get_color(matrix[i]);
    LEDs.setPixelColor(i, LEDs.Color(color[0], color[1], color[2]));
  }
  LEDs.show();
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
    if (r_c1.x == 1) {
      snake.moveUp();
    } else if (r_c1.x == 2) {
      snake.moveDown();
    } else if (r_c1.x == 3) {
      snake.moveLeft();
    } else if (r_c1.x == 4) {
      snake.moveRight();
    }

    Position_Vector apples = game.getApples();
    Position_Vector snakePos = snake.getBody();

    for (Position p : apples) {
      matrix[x_y_to_matrix(p.x, p.y)] = 1;
    }

    // head other color
    matrix[x_y_to_matrix(snakePos[0].x, snakePos[0].y)] = 2;
    for (int i = 1; i < snakePos.size(); i++) {
      matrix[x_y_to_matrix(snakePos[i].x, snakePos[i].y)] = 3;
    }
    for (int i = 0; i < NUM_PIXELS + 1; i++) {
      int* color = get_color(matrix[i]);
      LEDs.setPixelColor(i, LEDs.Color(color[0], color[1], color[2]));
    }
    LEDs.show();

    packetWaiting = false;  // don't touch - reset and wait for new message
  }

  // set data to CAN bus
  mpu.update();
  print_roll_pitch_yaw();
  w_c1.x = round(mpu.getRoll());
  w_c1.y = round(mpu.getPitch());
  w_c1.z = round(mpu.getYaw());
  w_c2.x = round(mpu.getAccX());
  w_c2.y = round(mpu.getAccY());
  w_c2.z = round(mpu.getAccZ());
  Serial.println(w_c1.x, 2);
  Serial.println(w_c1.y, 2);
  Serial.println(w_c1.z, 2);
  delay(10);
}