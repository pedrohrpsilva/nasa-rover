// nasa-rover-console.cpp : This file contains the 'main' function. Program execution begins and
// ends there.
//

#include <iostream>

#include <config-reader.h>
#include <config-validator.h>
#include <nasa-controller.h>
#include <rover-factory.h>

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

int main() {
  NasaConfigReader reader;
  NasaConfigValidator validator;
  NasaRoverFactory rover_factory;

  NasaController controller(&reader, &validator, &rover_factory);
  auto positions = controller.Play("../data/console-input.txt");

  for (auto position : positions) {
    std::cout << position.coordinate.x << " " << position.coordinate.y << " "
              << CardinalToString(position.cardinal) << "\n";
  }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add
//   existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln
//   file
