#include "gtest/gtest.h"

#include <config-validator.h>

Config GenerateValidConfig() {
    Config input{
        .upper_right_coordinate{.x = 5, .y = 5 },
        .rover_inputs = {
            RoverConfig{
                Position{1,1},
                {}
            }
        }
    };

    return input;
}

TEST(ConfigValidator, Success) {
    Config input = GenerateValidConfig();
    EXPECT_TRUE(NasaConfigValidator().Validate(input));
}

TEST(ConfigValidator, InvalidPlateuX) {
    Config input = GenerateValidConfig();
    input.upper_right_coordinate.x = -1;
    EXPECT_FALSE(NasaConfigValidator().Validate(input));
}

TEST(ConfigValidator, InvalidPlateuY) {
    Config input = GenerateValidConfig();
    input.upper_right_coordinate.y = -1;
    EXPECT_FALSE(NasaConfigValidator().Validate(input));
}

TEST(ConfigValidator, WithoutRover) {
    Config input = GenerateValidConfig();
    input.rover_inputs.clear();
    EXPECT_FALSE(NasaConfigValidator().Validate(input));
}

TEST(ConfigValidator, RoverOutsidePlateu) {
    Config input = GenerateValidConfig();
    input.rover_inputs[0].start_position.coordinate.x = 6;
    EXPECT_FALSE(NasaConfigValidator().Validate(input));

    input.rover_inputs[0].start_position.coordinate.x = -1;
    EXPECT_FALSE(NasaConfigValidator().Validate(input));

    input = GenerateValidConfig();
    input.rover_inputs[0].start_position.coordinate.y = -1;
    EXPECT_FALSE(NasaConfigValidator().Validate(input));

    input.rover_inputs[0].start_position.coordinate.y = 6;
    EXPECT_FALSE(NasaConfigValidator().Validate(input));
}