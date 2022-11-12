#include <nasa-controller.h>

#include "gtest/gtest.h"
#include "mocks.h"

TEST(NasaController, ConstructorFail) {
  EXPECT_THROW(NasaController(nullptr, nullptr, nullptr), NullPointerException);
}

TEST(NasaController, FailToReadConfigFile) {
  ExceptionReader reader;
  TrueValidator validator;
  DummyRoverFactory factory;

  EXPECT_THROW(NasaController(&reader, &validator, &factory).Play(""), ReadConfigFileException);
}

TEST(NasaController, FailToValidateConfigFile) {
  DummyReader reader;
  FalseValidator validator;
  DummyRoverFactory factory;

  EXPECT_THROW(NasaController(&reader, &validator, &factory).Play(""), ValidateConfigException);
}

TEST(NasaController, DummySuccess) {
  DummyReader reader;
  TrueValidator validator;
  DummyRoverFactory factory;

  auto result = NasaController(&reader, &validator, &factory).Play("");

  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].coordinate.x, 1);
  EXPECT_EQ(result[0].coordinate.y, 1);
  EXPECT_EQ(result[0].cardinal, Cardinal::kNorth);
}

TEST(NasaController, OutsideMovement) {
  DummyReader reader;
  TrueValidator validator;
  DummyRoverFactory factory(true);

  auto result = NasaController(&reader, &validator, &factory).Play("");

  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].coordinate.x, -1);
  EXPECT_EQ(result[0].coordinate.y, -1);
  EXPECT_EQ(result[0].cardinal, Cardinal::kNorth);
}

TEST(NasaController, SameConfigSameResult) {
  DummyReader reader;
  NasaConfigValidator validator;
  NasaRoverFactory factory;

  auto result_one = NasaController(&reader, &validator, &factory).Play("");
  auto result_two = NasaController(&reader, &validator, &factory).Play("");

  EXPECT_EQ(result_one.size(), result_two.size());
  EXPECT_EQ(result_one[0].coordinate.x, result_two[0].coordinate.x);
  EXPECT_EQ(result_one[0].coordinate.y, result_two[0].coordinate.y);
  EXPECT_EQ(result_one[0].cardinal, result_two[0].cardinal);
}