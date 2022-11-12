#include <plateau.h>

#include "gtest/gtest.h"

Coordinate RandomCoordinateInside(const Coordinate& right_upper) {
  int x = rand() % (right_upper.x + 1);
  int y = rand() % (right_upper.y + 1);

  return Coordinate{x, y};
}

TEST(OutsidePlateau, Inside) {
  Coordinate upper_right_coordinate{25, 25};
  Plateau plateua{upper_right_coordinate};

  const int kNumSamples = 100;
  for (int i = 0; i < kNumSamples; ++i) {
    auto coordinate = RandomCoordinateInside(upper_right_coordinate);

    EXPECT_FALSE(OutsidePlateau(plateua, coordinate));
  }
}

TEST(OutsidePlateau, Outside) {
  Coordinate upper_right_coordinate{25, 25};
  Plateau plateua{upper_right_coordinate};

  const int kNumSamples = 100;
  for (int i = 0; i < kNumSamples; ++i) {
    int delta = rand() % 100 + 1;
    EXPECT_TRUE(OutsidePlateau(plateua, Coordinate(-delta, -delta)));
    EXPECT_TRUE(OutsidePlateau(plateua, Coordinate(-delta, 0)));
    EXPECT_TRUE(OutsidePlateau(plateua, Coordinate(0, -delta)));
    EXPECT_TRUE(OutsidePlateau(
        plateua, Coordinate(upper_right_coordinate.x, upper_right_coordinate.y + delta)));
    EXPECT_TRUE(OutsidePlateau(
        plateua, Coordinate(upper_right_coordinate.x + delta, upper_right_coordinate.y)));
    EXPECT_TRUE(OutsidePlateau(
        plateua, Coordinate(upper_right_coordinate.x + delta, upper_right_coordinate.y + delta)));
  }
}