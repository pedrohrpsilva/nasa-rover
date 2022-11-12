#include "nasa-controller.h"

#include "plateau.h"

std::vector<Position> NasaController::Play(const std::string& filepath) {
  Config config;
  try {
    config = reader_->Read(filepath);
  } catch (std::exception&) {
    throw ReadConfigFileException();
  }

  Plateau plateau(config.upper_right_coordinate);

  if (!validator_->Validate(config)) {
    std::cout << "[ERROR] Invalid configuration. Check if the config file is right.";
    throw ValidateConfigException();
  }

  std::vector<Position> result;
  result.reserve(config.rover_inputs.size());
  for (int i = 0; i < static_cast<int>(config.rover_inputs.size()); ++i) {
    auto rover_config = config.rover_inputs[i];
    auto rover = rover_factory_->Create(rover_config.start_position);

    for (auto instruction : rover_config.instructions) {
      switch (instruction) {
        case Instruction::kMove:
          rover->Move();
          break;
        case Instruction::kTurnLeft:
          rover->TurnLeft();
          break;
        case Instruction::kTurnRight:
          rover->TurnRight();
          break;
        default:
          throw std::exception("This should not happen!");
      }

      if (OutsidePlateau(plateau, rover->GetPosition().coordinate)) {
        std::cout << "[ERROR] The Rover number " << i + 1 << " fell off the plateau.";
        break;
      }
    }

    result.push_back(rover->GetPosition());
  }

  return result;
}
