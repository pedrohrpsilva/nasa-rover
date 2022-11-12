#pragma once

#include <vector>
#include <string>

#include "config-reader.h"
#include "config-validator.h"
#include "rover-factory.h"

class NullPointerException : public std::exception {};

class NasaController {
public:
    // Pass all in constructor to follow RAII principles.
    explicit NasaController(IConfigReader* reader,
                            IConfigValidator* validator,
                            IRoverFactory* rover_factory) : rover_factory_(rover_factory), reader_(reader), validator_(validator) {
        if (!reader || !validator || !rover_factory) {
            throw NullPointerException();
        }
    }

    void Play(const std::string& filepath);

private:
    IRoverFactory* rover_factory_{};
    IConfigReader* reader_{};
    IConfigValidator* validator_{};
};
