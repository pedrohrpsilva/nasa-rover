#include "nasa-controller.h"

#include "plateau.h"

std::string CardinalToString(const Cardinal& cardinal) {
    switch (cardinal) {
    case Cardinal::kEast:
        return "E";
        break;
    case Cardinal::kNorth:
        return "N";
        break;
    case Cardinal::kSouth:
        return "S";
        break;
    case Cardinal::kWest:
        return "W";
        break;
    default:
        throw std::exception("Unexpected cardinal enum.");
    }
}

void NasaController::Play(const std::string& filepath)
{
    Config config = reader_->Read(filepath);

    Plateau plateau(config.upper_right_coordinate);

    if (!validator_->Validate(config)) {
        std::cout << "[ERROR] Invalid configuration. Check if the config file is right.";
        return;
    }

    for (int i = 0; i < static_cast<int>(config.rover_inputs.size()); ++i) {
        auto rover_config = config.rover_inputs[i];
        auto rover = rover_factory_->Create(rover_config.start_position);
        bool fell = false;

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
                fell = true;
                break;
            }
        }

        if (!fell) {
            std::cout << rover->GetPosition().coordinate.x << " "
                      << rover->GetPosition().coordinate.y << " "
                      << CardinalToString(rover->GetPosition().cardinal) << "\n";
        }
    }
}

