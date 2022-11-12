#pragma once

#include "config-reader.h"
#include "config-validator.h"
#include "rover-factory.h"
#include "rover.h"
#include "util.h"

// TODO(anyone): Use gmock library.
class ExceptionReader : public IConfigReader {
 public:
  const Config Read(const std::string& filepath) const override { throw std::exception(); };
};

class DummyReader : public IConfigReader {
 public:
  const Config Read(const std::string& filepath) const override { return GenerateValidConfig(); };
};

class TrueValidator : public IConfigValidator {
 public:
  bool Validate(const Config& config) const override { return true; }
};

class FalseValidator : public IConfigValidator {
 public:
  bool Validate(const Config& config) const override { return false; }
};

class DoNothingRover : public IRover {
 public:
  DoNothingRover(const Position& start_position) : position_(start_position) {}

  void Move() override {}
  void TurnLeft() override{};
  void TurnRight() override{};
  const Position& GetPosition() const override { return position_; }

 private:
  Position position_;
};

class FallingRover : public IRover {
 public:
  FallingRover(const Position& start_position) : position_(start_position) {}

  void Move() override { position_ = Position{Coordinate{-1, -1}, Cardinal::kNorth}; }
  void TurnLeft() override{};
  void TurnRight() override{};
  const Position& GetPosition() const override { return position_; }

 private:
  Position position_;
};

class DummyRoverFactory : public IRoverFactory {
 public:
  DummyRoverFactory(bool fall = false) : fall_(fall){};
  std::unique_ptr<IRover> Create(const Position& start_position) const override {
    if (fall_) {
      return std::move(std::make_unique<FallingRover>(start_position));
    } else {
      return std::move(std::make_unique<DoNothingRover>(start_position));
    }
  }

 private:
  bool fall_{};
};