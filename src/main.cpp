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

  int matrix[101] = {0};

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


  Position_Vector apples = getApples();
  Position_Vector snake = snake.getBody();

  for (Position p:apples) {
    matrix[x_y_to_matrix(p.x, p.y)] = 1;
  }
  
  // head other color
  matrix[x_y_to_matrix(snake[0].x, snake[0].y)] = 2;
  for (i=1; i<snake.size(); i++) {
    matrix[x_y_to_matrix(p.x, p.y)] = 3;
  }

  for(int i=1; i<NUM_PIXELS+1; i++) {
    LEDs.setPixelColor(i, LEDs.Color(matrix[i]));
  }
    LEDs.show();
}

int x_y_to_matrix(x, y)
{
  return (y-1)*10 + x;
}