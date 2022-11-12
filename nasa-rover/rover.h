#pragma once

#include "common.h"

class IRover {
public:
    virtual void Move() = 0;
    virtual void TurnLeft() = 0;
    virtual void TurnRight() = 0;

    virtual const Position& GetPosition() const = 0;
};

class NasaRover : public IRover {
public:
    explicit NasaRover(const Position& start_position) : position_(start_position) {}

    void Move() override {
        Coordinate old_coordinate = position_.coordinate;
        switch (position_.cardinal) {
        case Cardinal::kNorth:
            position_.coordinate = Coordinate{ old_coordinate.x, old_coordinate.y + 1 };
            break;
        case Cardinal::kSouth:
            position_.coordinate = Coordinate{ old_coordinate.x, old_coordinate.y - 1 };
            break;
        case Cardinal::kEast:
            position_.coordinate = Coordinate{ old_coordinate.x + 1, old_coordinate.y };
            break;
        case Cardinal::kWest:
            position_.coordinate = Coordinate{ old_coordinate.x - 1, old_coordinate.y };
            break;
        }
    }

    void TurnLeft() override {
        position_.cardinal = Cardinal((position_.cardinal + 5) % 4);
    };
    void TurnRight() override {
        position_.cardinal = Cardinal((position_.cardinal + 3) % 4);
    };

    const Position& GetPosition() const override { return position_; }

private:

    Position position_;
};
