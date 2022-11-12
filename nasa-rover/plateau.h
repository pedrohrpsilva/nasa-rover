#pragma once

#include "common.h"

// A Mars plateau represented by a rect defined from (0,0) as left-lower point and a upper-right
// coordinate passed as input.
struct Plateau {
  Coordinate upper_right_coordinate;
};

inline bool OutsidePlateau(const Plateau& plateau, const Coordinate& current_coordinate) {
  if (current_coordinate.x < 0 || current_coordinate.y < 0 ||
      current_coordinate.x > plateau.upper_right_coordinate.x ||
      current_coordinate.y > plateau.upper_right_coordinate.y) {
    return true;
  }

  return false;
}