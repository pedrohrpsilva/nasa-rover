#pragma once

#include <memory>

#include "common.h"
#include "rover.h"

class IRoverFactory {
public:
    virtual std::unique_ptr<IRover> Create(const Position& start_position) const = 0;
};

class NasaRoverFactory : public IRoverFactory {
public:
    std::unique_ptr<IRover> Create(const Position& start_position) const override {
        return std::move(std::make_unique<NasaRover>(start_position));
    }
};