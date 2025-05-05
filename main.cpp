#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Question
{
  std::string text;
  std::string type;
};

class Survey
{
  private:
  std::string surveyName;
  std::vector<Question> questions;
  std::vector<std::string> responses;
  
  bool validateResponses(const std::string& response, const std::string& type)
  {
    if (type == "yes/no")
    {
      return (response == "Y" || response == "N" || response == "y" || response == "n");
    }
    else if (type == "number")
    {
      return !response.empty() && std::all_of(response.begin(), response.end(), isdigit);
    }

    return true;
  }

  public:
  Survey(std::string name) : surveyName(name) {}

  void addQuestion(const std::string& text, const std::string& type = "open")
  {
    questions.push_back({text, type});
  }

  void conductSurvey()
  {
    std::cout << surveyName << " Survey" << std::endl;
    std::cout << std::endl;

    for(size_t i = 0; i < questions.size(); i++)
    {
      bool validResponse = false;
      while (!validResponse)
      {
        std::cout << i + 1 << ". " << questions[i].text << " ";
        if (questions[i].type == "yesno")
        {
          std::cout << "(Y/N): ";
        }
        else if (questions[i].type == "number")
        {
          std::cout << "(Enter a number): ";
          std::getline(std::cin, responses[i]);

          validResponse = validateResponses(responses[i], questions[i].type);
          if (!validResponse)
          {
            std::cout << "Invalid input. Please try again!" << std::endl;
          }
        }
      }
    }
  }

  void saveResults()
  {}
};

void initializeSurvey(Question questions[], int num, std::string responses[])
{
  for (int i = 0; i < num; i++)
  {
    std::cout << questions[i].text << " ";
    std::getline(std::cin, responses[i]);
  }
}

int main()
{
  const int num = 1;
  Question questions[num] = {
    {"How to say hello world in C++?"},
  };

  std::string responses[num];

  std::cout << "Enzo's Survey" << std::endl;
  initializeSurvey(questions, num, responses);

  std::cout << "End" << std::endl;

  return 0;
}