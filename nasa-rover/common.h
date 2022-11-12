#pragma once

#include <vector>

// Represent a combination of x and y co-ordinates in Plateau.
struct Coordinate {
  int x;
  int y;
};

// Represent the four cardinal compass points.
// Do not alter the order!
// This order was take to speed-up the process of turn left/right.
enum Cardinal { kNorth = 0, kWest, kSouth, kEast };

// Represent a position that the Rover could be.
struct Position {
  Coordinate coordinate;
  Cardinal cardinal;
};

enum Instruction { kTurnLeft, kTurnRight, kMove };

struct RoverConfig {
  Position start_position;
  std::vector<Instruction> instructions;
};

struct Config {
  Coordinate upper_right_coordinate;
  std::vector<RoverConfig> rover_inputs;
};
