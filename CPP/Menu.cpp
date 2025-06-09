#include <iostream>
#include "Menu.h"

void displayMenu()
{
  std::cout << "\n=== Survey System Menu ===" << std::endl;
  std::cout << "1. Create a new survey" << std::endl;
  std::cout << "2. Take a survey" << std::endl;
  std::cout << "3. View survey results" << std::endl;
  std::cout << "4. Save survey results" << std::endl;
  std::cout << "5. Load survey from file" << std::endl;
  std::cout << "6. Exit" << std::endl;
  std::cout << "Enter choice (1-6): ";
}