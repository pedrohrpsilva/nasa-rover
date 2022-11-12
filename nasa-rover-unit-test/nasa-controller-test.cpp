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