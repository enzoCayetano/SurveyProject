#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "Survey.h"

void displayMenu() 
{
  std::cout << "\n=== Survey System Menu ===\n";
  std::cout << "1. Create a new survey\n";
  std::cout << "2. Take a survey\n";
  std::cout << "3. View survey results\n";
  std::cout << "4. Save survey results\n";
  std::cout << "5. Load survey from file\n";
  std::cout << "6. Exit\n";
  std::cout << "Enter choice (1-6): ";
}

int main()
{
  std::vector<Survey> surveys;
  bool running = true;

  while (running) 
  {
    displayMenu();
    int choice;
    if (!(std::cin >> choice)) 
    {
      std::cout << "Invalid input. Please enter a number.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) 
    {
      case 1: 
      {
        std::string name;
        std::cout << "Enter survey name: ";
        std::getline(std::cin, name);
        Survey survey(name);

        std::cout << "Enter number of questions: ";
        int numQuestions;
        if (!(std::cin >> numQuestions) || numQuestions < 1) 
        {
          std::cout << "Invalid number. Survey not created.\n";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int i = 0; i < numQuestions; ++i) 
        {
          std::string text, type;
          std::cout << "Enter question " << i + 1 << " text: ";
          std::getline(std::cin, text);
          std::cout << "Enter question type (open, yes/no, number, multiple-choice, rating): ";
          std::getline(std::cin, type);
          std::vector<std::string> options;
          if (type == "multiple-choice") 
          {
            std::cout << "Enter number of options: ";
            int numOptions;
            if (!(std::cin >> numOptions) || numOptions < 2) 
            {
              std::cout << "Invalid number of options. Using open type.\n";
              type = "open";
            }
            else 
            {
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              for (int j = 0; j < numOptions; ++j) 
              {
                std::string option;
                std::cout << "Enter option " << j + 1 << ": ";
                std::getline(std::cin, option);
                options.push_back(option);
              }
            }
          }
          survey.addQuestion(text, type, options);
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        surveys.push_back(survey);
        std::cout << "Survey '" << name << "' created.\n";
        break;
      }
      case 2: 
      {
        if (surveys.empty()) 
        {
          std::cout << "No surveys available.\n";
          break;
        }
        std::cout << "Available surveys:\n";
        for (size_t i = 0; i < surveys.size(); ++i) 
        {
          std::cout << i + 1 << ". " << surveys[i].getName() << " (" << surveys[i].getQuestionCount() << " questions)" << std::endl;
        }
        std::cout << "Select survey (1-" << surveys.size() << "): ";
        int surveyIndex;
        if (!(std::cin >> surveyIndex) || surveyIndex < 1 || surveyIndex > static_cast<int>(surveys.size())) 
        {
          std::cout << "Invalid selection." << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        surveys[surveyIndex - 1].conductSurvey();
        break;
      }
      case 3:
      {
        if (surveys.empty()) 
        {
          std::cout << "No surveys available." << std::endl;
          break;
        }
        std::cout << "Available surveys:" << std::endl;
        for (size_t i = 0; i < surveys.size(); ++i) 
        {
          std::cout << i + 1 << ". " << surveys[i].getName() << "\n";
        }
        std::cout << "Select survey to view results (1-" << surveys.size() << "): ";
        int surveyIndex;
        if (!(std::cin >> surveyIndex) || surveyIndex < 1 || surveyIndex > static_cast<int>(surveys.size())) 
        {
          std::cout << "Invalid selection." << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        surveys[surveyIndex - 1].viewResults();
        break;
      }
      case 4: 
      {
        if (surveys.empty()) 
        {
          std::cout << "No surveys available." << std::endl;
          break;
        }

        std::cout << "Available surveys:" << std::endl;
        for (size_t i = 0; i < surveys.size(); ++i) 
        {
          std::cout << i + 1 << ". " << surveys[i].getName() << "\n";
        }

        int surveyIndex;
        std::cout << "Select survey to save (1-" << surveys.size() << "): ";
        if (!(std::cin >> surveyIndex) || surveyIndex < 1 || surveyIndex > static_cast<int>(surveys.size())) 
        {
          std::cout << "Invalid selection." << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string filename;
        std::cout << "Enter filename to save results: ";
        std::getline(std::cin, filename);
        surveys[surveyIndex - 1].saveResults(filename);
        break;
      }
      case 5: 
      {
        std::string filename;
        std::cout << "Enter filename to load survey: ";
        std::getline(std::cin, filename);
        Survey survey("Loaded Survey");
        if (survey.loadFromFile(filename)) 
        {
          surveys.push_back(survey);
          std::cout << "Survey loaded successfully." << std::endl;
        } 
        else 
        {
          std::cout << "Failed to load survey." << std::endl;
        }
        break;
      }
      case 6:
        running = false;
        std::cout << "Exiting program." << std::endl;
        break;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }

  return 0;
}