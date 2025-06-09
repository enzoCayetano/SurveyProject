#include "Survey.h"
#include <iostream>
#include <algorithm>
#include <cctype>

Survey::Survey(const std::string& name) : surveyName(name) {}

bool Survey::validateResponse(const std::string& response, const Question& question) 
{
  const std::string& type = question.getType();

  if (type == "yes/no") 
  {
    return (response == "Y" || response == "N" || response == "y" || response == "n");
  } 
  else if (type == "number") 
  {
    return !response.empty() && std::all_of(response.begin(), response.end(), ::isdigit);
  } 
  else if (type == "multiple-choice") 
  {
    try 
    {
      int choice = std::stoi(response);
      return choice > 0 && choice <= static_cast<int>(question.getOptions().size());
    } 
    catch (...)
    {
      return false;
    }
  } 
  else if (type == "rating") 
  {
    try 
    {
      int rating = std::stoi(response);
      return rating >= 1 && rating <= 5;
    } 
    catch (...) 
    {
      return false;
    }
  }
  return true;
}

void Survey::addQuestion(const std::string& text, const std::string& type, const std::vector<std::string>& options) 
{
  questions.push_back({text, type, options});
}

void Survey::conductSurvey() 
{
  std::cout << "\n=== " << surveyName << " Survey ===\n\n";
  std::vector<std::string> responses(questions.size());

  for (size_t i = 0; i < questions.size(); ++i) 
  {
    const Question& q = questions[i];
    bool validResponse = false;
    std::string response;

    while (!validResponse) 
    {
      std::cout << i + 1 << ". " << q.getText() << std::endl;

      const std::string& type = q.getType();

      if (type == "yes/no") 
      {
        std::cout << "(Y/N): ";
      } 
      else if (type == "number") 
      {
        std::cout << "(Enter a number): ";
      } 
      else if (type == "multiple-choice") 
      {
        const auto& opts = q.getOptions();
        for (size_t j = 0; j < opts.size(); ++j) 
        {
          std::cout << j + 1 << ") " << opts[j] << std::endl;
        }
        std::cout << "Enter choice (1-" << opts.size() << "): ";
      } 
      else if (type == "rating") 
      {
        std::cout << "(Enter rating 1-5): ";
      } 
      else 
      {
        std::cout << "(Open-ended): ";
      }

      std::getline(std::cin, response);
      if (response.empty() && type != "open") 
      {
        std::cout << "Sorry, the response cannot be empty. Please try again." << std::endl;
        continue;
      }

      validResponse = validateResponse(response, q);
      if (!validResponse) 
      {
        std::cout << "Invalid input. Please try again." << std::endl;
      } 
      else 
      {
        responses[i] = response;
      }
    }
  }

  allResponses.push_back(responses);
  std::cout << std::endl;
  std::cout << "Survey completed! Thank you." << std::endl;
}

void Survey::preview() const
{
  std::cout << "Survey Name: " << surveyName << std::endl;
  for (size_t i = 0; i < questions.size(); ++i) 
  {
    std::cout << i + 1 << ". " << questions[i].getText() << " [" << questions[i].getType() << "]" << std::endl;
    if (questions[i].getType() == "multiple-choice") 
    {
      const auto& opts = questions[i].getOptions();
      for (size_t j = 0; j < opts.size(); ++j) 
      {
        std::cout << "   - " << opts[j] << std::endl;
      }
    }
  }
}

void Survey::saveResults(const std::string& filename) 
{
  std::ofstream outFile(filename, std::ios::app);
  if (!outFile) 
  {
    std::cerr << "Error: Could not open file " << filename << "." << std::endl;
    return;
  }

  outFile << "Survey: " << surveyName << std::endl;
  for (const auto& responseSet : allResponses) 
  {
    outFile << "Response Set:" << std::endl;
    for (size_t i = 0; i < responseSet.size(); ++i) 
    {
      outFile << i + 1 << ". " << questions[i].getText() << ": " << responseSet[i] << std::endl;
    }
    outFile << std::endl;
  }
  outFile.close();
  std::cout << "Results saved to " << filename << std::endl;
}

bool Survey::loadFromFile(const std::string& filename) 
{
  std::ifstream inFile(filename);
  if (!inFile) 
  {
      std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
      return false;
  }

  questions.clear();
  allResponses.clear();
  std::string line;
  while (std::getline(inFile, line)) 
  {
    if (line.find("Survey: ") == 0) 
    {
      surveyName = line.substr(8);
    } 
    else if (line.find("Question: ") == 0) 
    {
      std::string text = line.substr(10);
      std::getline(inFile, line);
      std::string type = line.substr(6);
      questions.push_back({text, type});
    }
  }
  inFile.close();
  return true;
}

void Survey::viewResults() const 
{
  if (allResponses.empty()) 
  {
    std::cout << "No responses recorded for " << surveyName << "." << std::endl;
    return;
  }

  std::cout << std::endl;
  std::cout << "=== Results for " << surveyName << " ===" << std::endl;
  for (size_t set = 0; set < allResponses.size(); ++set) 
  {
    std::cout << std::endl;
    std::cout << "Response Set " << set + 1 << ":" << std::endl;
    for (size_t i = 0; i < allResponses[set].size(); ++i) 
    {
        std::cout << i + 1 << ". " << questions[i].getText() << ": " << allResponses[set][i] << std::endl;
    }
  }
}