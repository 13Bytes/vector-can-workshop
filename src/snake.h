#pragma once

#include <deque>

#include "game.h"

/**
 * @class Snake
 * @brief Represents a snake in the game.
 *
 * The Snake class encapsulates the behavior and state of a snake
 * in the game, including its movement and body.
 */
class Snake {
 public:
  /**
   * @brief Constructor for Snake.
   * @param game The game instance to which this snake belongs.
   *
   * Initializes a new Snake instance with a reference to the game.
   */
  Snake(Game *game);

  /**
   * @brief Moves the snake up.
   *
   * Adjusts the snake's position to simulate movement upwards.
   */
  void moveUp();

  /**
   * @brief Moves the snake down.
   *
   * Adjusts the snake's position to simulate movement downwards.
   */
  void moveDown();

  /**
   * @brief Moves the snake left.
   *
   * Adjusts the snake's position to simulate movement to the left.
   */
  void moveLeft();

  /**
   * @brief Moves the snake right.
   *
   * Adjusts the snake's position to simulate movement to the right.
   */
  void moveRight();

  /**
   * @brief Gets the length of the snake.
   * @return The length of the snake.
   */
  int getLength();

  /**
   * @brief Gets the body of the snake.
   * @return A vector representing the positions of the snake's body segments.
   */
  Position_Vector getBody();

 private:
  const int mapSize = 10;     ///< The size of the game map.
  Game *game;                 ///< The game instance.
  std::deque<Position> body;  ///< Deque representing the snake's body positions.
  Direction direction;        ///< Current direction of the snake's movement.

  /**
   * @brief Initializes the snake's body.
   *
   * Sets up the initial state and position of the snake's body.
   */
  void initializeBody();

  /**
   * @brief Gets the neighboring position based on the current position and direction.
   * @param position The current position.
   * @param direction The direction of movement.
   * @return The new position after moving in the given direction.
   */
  Position getNeighboringPosition(Position position, Direction direction);

  /**
   * @brief Calculates the modulo of a and b.
   * @param a The dividend, can be negative.
   * @param b The divisor.
   * @return The result of a modulo b.
   *
   * Returns a mod b. Also works with negative numbers as a.
   */
  int mod(int a, int b);
};