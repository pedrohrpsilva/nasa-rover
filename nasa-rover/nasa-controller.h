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

  std::vector<Position> Play(const std::string& filepath);

 private:
  IRoverFactory* rover_factory_{};
  IConfigReader* reader_{};
  IConfigValidator* validator_{};
};
