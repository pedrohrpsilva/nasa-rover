#pragma once

#include <string>
#include <vector>

#include "config-reader.h"
#include "config-validator.h"
#include "rover-factory.h"

class NullPointerException : public std::exception {};
class ReadConfigFileException : public std::exception {};
class ValidateConfigException : public std::exception {};

// TODO(anyone): In the future, check if a Factory should be used instead use exception.

// This service is responsible to control the Rover from the config readed from the file.
// Some assumptions were followed to define the behavior taken:
// 1- N-rovers could be in the same position.
// 2- The rover could fall from plateau (outside of plateau). In this case, the rover stop to move.
// 3- The fall of a rover does not end the operation.
class NasaController {
 public:
  explicit NasaController(IConfigReader* reader,
                          IConfigValidator* validator,
                          IRoverFactory* rover_factory)
      : rover_factory_(rover_factory), reader_(reader), validator_(validator) {
    // Emit exception if the construction off the Object failed.
    // The construction will be considered fail when a null-pointer service be passed as argument.
    // This behavior try to follow RAII principle.
    if (!reader || !validator || !rover_factory) {
      throw NullPointerException();
    }
  }

  // Read the config file and execute the instructions to all rovers.
  // If success, returns the end positions of all Rovers. Otherwise, a exception will be emited.
  std::vector<Position> Play(const std::string& filepath);

 private:
  IRoverFactory* rover_factory_{};
  IConfigReader* reader_{};
  IConfigValidator* validator_{};
};
