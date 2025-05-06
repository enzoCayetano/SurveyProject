#include <iostream>
#include "SurveyManager.h"

void SurveyManager::addSurvey(const Survey& survey) 
{
  surveys.push_back(survey);
}

void SurveyManager::listSurveys() const 
{
  if (surveys.empty()) 
  {
    std::cout << "No surveys available." << std::endl;
    return;
  }

  for (size_t i = 0; i < surveys.size(); ++i) 
  {
    std::cout << i + 1 << ". " << surveys[i].getName() << std::endl;
  }
}

bool SurveyManager::saveSurvey(size_t index, const std::string& filename) 
{
  if (index >= surveys.size()) return false;
  surveys[index].saveResults(filename);
  return true;
}

bool SurveyManager::loadSurvey(const std::string& filename) 
{
  Survey survey("Loaded Survey");
  if (survey.loadFromFile(filename)) 
  {
    surveys.push_back(survey);
    return true;
  }
  return false;
}

size_t SurveyManager::surveyCount() const 
{
  return surveys.size();
}

Survey* SurveyManager::getSurvey(size_t index) 
{
  if (index >= surveys.size()) return nullptr;
  return &surveys[index];
}