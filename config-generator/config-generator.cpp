// config-generator.cpp : This file contains the 'main' function. Program execution begins and ends
// there.
//

#include <fstream>
#include <iostream>
#include <stdlib.h>

#include <common.h>

Coordinate RandomCoordinateInside(const Coordinate& right_upper) {
  int x = rand() % (right_upper.x + 1);
  int y = rand() % (right_upper.y + 1);

  return Coordinate{x, y};
}

std::vector<Instruction> RandomInstructions(int num_instructions) {
  std::vector<Instruction> vector;
  vector.reserve(num_instructions);
  for (int i = 0; i < num_instructions; ++i) {
    vector.push_back(Instruction(rand() % 3));
  }

  return vector;
}

int main() {
  srand(time(0));
  // Generate plateau between 10x10 to 110x110.
  int plateau_x = rand() % 100 + 10;
  int plateau_y = rand() % 100 + 10;

  int kNumInstruction = 15;
  int kNumRovers = 2;

  std::ofstream file("../data/random-config.txt");

  file << plateau_x << " " << plateau_y << "\n";

  for (int i = 0; i < kNumRovers; ++i) {
    auto coordinate = RandomCoordinateInside(Coordinate{plateau_x, plateau_y});
    file << coordinate.x << " " << coordinate.y << " N"
         << "\n";

    std::string instruction_str;
    std::vector<Instruction> instrunctions = RandomInstructions(kNumInstruction);
    for (auto instruction : instrunctions) {
      switch (instruction) {
        case Instruction::kMove:
          instruction_str.append("M");
          break;
        case Instruction::kTurnLeft:
          instruction_str.append("L");
          break;
        case Instruction::kTurnRight:
          instruction_str.append("R");
          break;
      }
    }
    file << instruction_str << "\n";
  }

  file.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add
//   existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln
//   file
