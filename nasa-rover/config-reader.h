#pragma once

#include <exception>
#include <iostream>
#include <string>

#include "common.h"

class InvalidCardinalException : public std::exception {};
class InvalidFilePathException : public std::exception {};
class InvalidFileException : public std::exception {};
class InvalidInstructionException : public std::exception {};

// This service is responsible to read Input Configuration from a file.
// If success, the function returns the Config readed from file.
// Otherwise, the function returns a exception.
class IConfigReader {
 public:
  virtual const Config Read(const std::string& filepath) const = 0;
};

class NasaConfigReader : public IConfigReader {
 public:
  const Config Read(const std::string& filepath) const override;
};