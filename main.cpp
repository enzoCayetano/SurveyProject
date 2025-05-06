#include <iostream>
#include <string>
#include <limits>
#include "SurveyManager.h"
#include "SurveyIO.h"
#include "Menu.h"

int main() 
{
  SurveyManager manager;
  bool running = true;

  while (running) 
  {
    displayMenu();

    int choice;
    if (!(std::cin >> choice)) 
    {
      std::cout << "Invalid input. Please enter a number." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) 
    {
      case 1: 
      {
        std::string name;
        std::cout << std::endl;
        std::cout << "Enter survey name: ";
        std::getline(std::cin, name);
        Survey survey(name);

        int numQuestions;
        std::cout << "Enter number of questions: ";
        if (!(std::cin >> numQuestions) || numQuestions < 1) 
        {
          std::cout << "Invalid number. Survey not created." << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
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
            int numOptions;
            std::cout << "Enter number of options: ";
            if (!(std::cin >> numOptions) || numOptions < 2) 
            {
              std::cout << "Invalid number. Defaulting to open type." << std::endl;
              type = "open";
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } 
            else 
            {
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
        }

        manager.addSurvey(survey);
        std::cout << "Survey '" << name << "' created." << std::endl;
        break;
      }

      case 2: 
      {
        if (manager.surveyCount() == 0) 
        {
          std::cout << "\nNo surveys available.\n";
          break;
        }

        std::cout << std::endl;
        manager.listSurveys();
        std::cout << "Select survey to conduct (1-" << manager.surveyCount() << "): ";
        int index;
        if (!(std::cin >> index) || index < 1 || index > static_cast<int>(manager.surveyCount())) 
        {
          std::cout << "Invalid selection." << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Survey* selected = manager.getSurvey(index - 1);
        if (selected)
        {
          std::cout << "\n--- Survey Preview ---\n";
          selected->preview();
          std::cout << std::endl;
          std::cout << "Do you want to take this survey? (y/n): ";
          char confirm;
          std::cin >> confirm;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          if (confirm == 'y' || confirm == 'Y') 
          {
            selected->conductSurvey();
          }
          else 
          {
            std::cout << "Survey cancelled." << std::endl;
          }
        }
        break;
      }

      case 3: 
      {
        if (manager.surveyCount() == 0) 
        {
          std::cout << "\nNo surveys available.\n";
          break;
        }

        manager.listSurveys();
        std::cout << "Select survey to view results (1-" << manager.surveyCount() << "): ";
        int index;
        if (!(std::cin >> index) || index < 1 || index > static_cast<int>(manager.surveyCount())) 
        {
          std::cout << "Invalid selection.\n";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Survey* selected = manager.getSurvey(index - 1);
        if (selected) selected->viewResults();
        break;
      }

      case 4: 
      {
        if (manager.surveyCount() == 0) 
        {
          std::cout << "\nNo surveys available.\n";
          break;
        }

        manager.listSurveys();
        std::cout << "Select survey to save (1-" << manager.surveyCount() << "): ";
        int index;
        if (!(std::cin >> index) || index < 1 || index > static_cast<int>(manager.surveyCount())) 
        {
          std::cout << "Invalid selection." << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string filename;
        std::cout << "Enter filename to save results: ";
        std::getline(std::cin, filename);

        if (!SurveyIO::saveSurvey(*manager.getSurvey(index - 1), filename)) 
        {
          std::cout << "Failed to save survey." << std::endl;
        }
        break;
      }

      case 5: 
      {
        std::string filename;
        std::cout << "\nEnter filename to load survey: ";
        std::getline(std::cin, filename);

        Survey loaded("Loaded Survey");
        if (SurveyIO::loadSurvey(loaded, filename)) 
        {
          manager.addSurvey(loaded);
          std::cout << "Survey loaded successfully." << std::endl;
        } 
        else 
        {
          std::cout << "Failed to load survey." << std::endl;
        }
        break;
      }

      case 6:
        std::cout << "\nExiting program.\n";
        running = false;
        break;

      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }

  return 0;
}