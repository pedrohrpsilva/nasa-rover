#include <config-reader.cpp>

#include "gtest/gtest.h"

TEST(ParseCoordinate, MissingCoordinate) {
  EXPECT_THROW(ParseCoordinate("5"), InvalidFileException);
}

TEST(ParseCoordinate, ThreeDCoordinate) {
  EXPECT_THROW(ParseCoordinate("1 2 3"), InvalidFileException);
}

TEST(ParseCoordinate, CoordinateAsString) {
  EXPECT_THROW(ParseCoordinate("x y"), InvalidFileException);
}

TEST(ParseCoordinate, DifferentDelimiter) {
  EXPECT_THROW(ParseCoordinate("1, 1"), InvalidFileException);
}

TEST(ParsePosition, Success) {
  auto position = ParsePosition("1 1 N");
  EXPECT_EQ(position.coordinate.x, 1);
  EXPECT_EQ(position.coordinate.y, 1);
  EXPECT_EQ(position.cardinal, Cardinal::kNorth);
}

TEST(ParsePosition, MissingCardinal) {
  EXPECT_THROW(ParsePosition("1 1"), InvalidFileException);
}

TEST(ParsePosition, MissingPosition) {
  EXPECT_THROW(ParsePosition("N"), InvalidFileException);
}

TEST(ParsePosition, InvalidCardinalValue) {
  EXPECT_THROW(ParsePosition("1 1 F"), InvalidCardinalException);
}

TEST(ParsePosition, DifferentDelimiter) {
  EXPECT_THROW(ParsePosition("1, 1, N"), InvalidFileException);
}

// ParseInstruction
TEST(ParseInstruction, Success) {
  Instruction move = ParseInstruction('M');
  Instruction turn_left = ParseInstruction('L');
  Instruction turn_right = ParseInstruction('R');

  EXPECT_EQ(move, Instruction::kMove);
  EXPECT_EQ(turn_left, Instruction::kTurnLeft);
  EXPECT_EQ(turn_right, Instruction::kTurnRight);
}

TEST(ParseInstruction, InvalidInstruction) {
  EXPECT_THROW(ParseInstruction('A'), InvalidInstructionException);
}

TEST(NasaConfigReader, FailToReadFile) {
  NasaConfigReader reader;
  EXPECT_THROW(reader.Read("invalid_path"), InvalidFilePathException);
}

TEST(NasaConfigReader, Success) {
  NasaConfigReader reader;
  auto input = reader.Read("../data/success.txt");

  EXPECT_EQ(input.upper_right_coordinate.x, 5);
  EXPECT_EQ(input.upper_right_coordinate.y, 5);
  EXPECT_EQ(input.rover_inputs.size(), 2);
  EXPECT_EQ(input.rover_inputs[0].start_position.cardinal, Cardinal::kNorth);
  EXPECT_EQ(input.rover_inputs[0].start_position.coordinate.x, 1);
  EXPECT_EQ(input.rover_inputs[0].start_position.coordinate.y, 2);
  EXPECT_EQ(input.rover_inputs[0].instructions.size(), 2);
  EXPECT_EQ(input.rover_inputs[0].instructions[0], Instruction::kTurnLeft);
  EXPECT_EQ(input.rover_inputs[0].instructions[1], Instruction::kMove);
  EXPECT_EQ(input.rover_inputs[1].start_position.cardinal, Cardinal::kEast);
  EXPECT_EQ(input.rover_inputs[1].start_position.coordinate.x, 3);
  EXPECT_EQ(input.rover_inputs[1].start_position.coordinate.y, 3);
  EXPECT_EQ(input.rover_inputs[1].instructions.size(), 2);
  EXPECT_EQ(input.rover_inputs[1].instructions[0], Instruction::kMove);
  EXPECT_EQ(input.rover_inputs[1].instructions[1], Instruction::kTurnRight);
}