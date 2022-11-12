#pragma once

#include "common.h"
#include "plateau.h"

class IConfigValidator {
public:
    virtual bool Validate(const Config& input) const = 0;
};

class NasaConfigValidator : public IConfigValidator {
public:
    bool Validate(const Config& config) const override {
        // Upper right coordinate must be greater than (0,0).
        if (config.upper_right_coordinate.x < 0 || config.upper_right_coordinate.y < 0)
            return false;

        // The user must pass a rover input.
        if (config.rover_inputs.size() == 0)
            return false;

        Plateau plateau{ config.upper_right_coordinate };
        // Rover start position must not be outside plateau.
        for (auto rover : config.rover_inputs) {
            if (OutsidePlateau(plateau, rover.start_position.coordinate)) {
                return false;
            }
        }

        return true;
    }
};