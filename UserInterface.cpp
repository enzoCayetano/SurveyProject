#include <iostream>
#include <string>
#include <limits>
#include "UserInterface.h"
#include "SurveyIO.h"
#include "Menu.h"

UserInterface::UserInterface() {}

void UserInterface::executeInterface() 
{
  loginMenu();
}

void UserInterface::loginMenu() 
{
  bool loggedIn = false;

    while (!loggedIn) 
    {
      std::cout << "\nSelect role:\n1. User\n2. Admin\n3. Exit\nChoice: ";
      int choice;
      std::cin >> choice;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      switch (choice) 
      {
        case 1:
          userPanel();
          // loggedIn = true;
          break;
        case 2:
          adminPanel();
          // loggedIn = true;
          break;
        case 3:
          std::cout << "Exiting..." << std::endl;
          return;
        default:
          std::cout << "Invalid choice." << std::endl;
      }
    }
}

void UserInterface::userPanel() 
{
  bool running = true;

  while (running) 
  {
    std::cout << "\n--- User Panel ---\n";
    std::cout << "1. Take Survey\n2. View Survey Results\n3. Back\nChoice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) 
    {
      case 1:
        if (manager.surveyCount() == 0) 
        {
          std::cout << "No surveys available." << std::endl;
          break;
        }
        manager.listSurveys();
        std::cout << "Select survey: ";
        int index;
        std::cin >> index;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (Survey* s = manager.getSurvey(index - 1)) {
          s->conductSurvey();
        } 
        else 
        {
          std::cout << "Invalid survey." << std::endl;
        }
        break;
      case 2:
        if (manager.surveyCount() == 0) 
        {
          std::cout << "No surveys available." << std::endl;
          break;
        }
        manager.listSurveys();
        std::cout << "Select survey: ";
        std::cin >> index;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (Survey* s = manager.getSurvey(index - 1)) {
          s->viewResults();
        } 
        else 
        {
          std::cout << "Invalid survey." << std::endl;
        }
        break;
      case 3:
        running = false;
        break;
      default:
        std::cout << "Invalid input." << std::endl;
    }
  }
}

void UserInterface::adminPanel() 
{
  bool running = true;

  while (running) 
  {
    std::cout << "\n--- Admin Panel ---\n";
    std::cout << "1. Create Survey\n2. Save Survey\n3. Load Survey\n4. Back\nChoice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) 
    {
      case 1: 
      {
        std::string name;
        std::cout << "\nEnter survey name: ";
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
      case 3: 
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
      case 4:
        running = false;
        break;
      default:
        std::cout << "Invalid input." << std::endl;
    }
  }
}