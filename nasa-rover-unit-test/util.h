#pragma once

#include "common.h"

inline Config GenerateValidConfig() {
  Config input{.upper_right_coordinate{.x = 5, .y = 5},
               .rover_inputs = {RoverConfig{Position{Coordinate{1, 1}, Cardinal::kNorth},
                                            {Instruction::kTurnLeft, Instruction::kMove}}}};

  return input;
}