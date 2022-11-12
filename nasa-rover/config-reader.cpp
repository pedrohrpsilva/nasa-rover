#include "config-reader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

template <typename T>
void GetValue(std::istringstream& stream, T& value) {
  if (!stream.good()) {
    throw InvalidFileException();
  }
  stream >> value;
}

Coordinate ParseCoordinate(const std::string& coordinate_string) {
  std::istringstream stream(coordinate_string);

  int x;
  int y;

  GetValue(stream, x);
  GetValue(stream, y);

  // Check if we have some parse exception
  if (stream.fail()) {
    throw InvalidFileException();
  }

  // EOF.
  stream.get();
  // The coordinate line must finish after y. If not, the file could be corrupted.
  if (!stream.eof()) {
    throw InvalidFileException();
  }

  return Coordinate{x, y};
}

Position ParsePosition(const std::string& string) {
  std::istringstream stream(string);

  int x;
  int y;
  char cardinal_char;

  GetValue(stream, x);
  GetValue(stream, y);
  GetValue(stream, cardinal_char);

  // Check if we have some parse exception
  if (stream.fail()) {
    throw InvalidFileException();
  }

  // EOF.
  stream.get();
  // The position line must finish after cardinal. If not, the file could be corrupted.
  if (!stream.eof()) {
    throw InvalidFileException();
  }

  Cardinal cardinal;
  switch (std::toupper(cardinal_char)) {
    case 'N':
      cardinal = Cardinal::kNorth;
      break;
    case 'S':
      cardinal = Cardinal::kSouth;
      break;
    case 'E':
      cardinal = Cardinal::kEast;
      break;
    case 'W':
      cardinal = Cardinal::kWest;
      break;
    default:
      throw InvalidCardinalException();
  }

  return Position{Coordinate{x, y}, cardinal};
}

Instruction ParseInstruction(const char& instruction_char) {
  switch (std::toupper(instruction_char)) {
    case 'L':
      return Instruction::kTurnLeft;
    case 'R':
      return Instruction::kTurnRight;
    case 'M':
      return Instruction::kMove;
    default:
      throw InvalidInstructionException();
  }
}

const Config NasaConfigReader::Read(const std::string& filepath) const {
  std::fstream file;
  file.open(filepath);

  if (!file.is_open()) {
    throw InvalidFilePathException();
  }

  std::string plateu_input;
  std::getline(file, plateu_input);

  Config input;
  input.upper_right_coordinate = ParseCoordinate(plateu_input);

  std::string rover_start_position_str;
  std::string rover_instructions_str;
  // First read the rover's start position line.
  while (std::getline(file, rover_start_position_str)) {
    // After read the rover's instructions line.
    if (!std::getline(file, rover_instructions_str)) {
      throw InvalidFileException();
    }

    Position rover_start_position = ParsePosition(rover_start_position_str);
    std::vector<Instruction> instructions;
    for (auto c : rover_instructions_str) {
      instructions.push_back(ParseInstruction(c));
    }

    input.rover_inputs.push_back(RoverConfig{rover_start_position, instructions});
  }

  return input;
}
