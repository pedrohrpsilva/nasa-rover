#pragma once

#include <exception>
#include <iostream>
#include <string>

#include "common.h"

class InvalidCardinalException : public std::exception {};
class InvalidFilePathException : public std::exception {};
class InvalidFileException : public std::exception {};
class InvalidInstructionException : public std::exception {};

class IConfigReader {
 public:
  virtual const Config Read(const std::string& filepath) const = 0;
};

class NasaConfigReader : public IConfigReader {
 public:
  const Config Read(const std::string& filepath) const override;
};