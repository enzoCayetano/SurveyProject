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

size_t SurveyManager::surveyCount() const 
{
  return surveys.size();
}

Survey* SurveyManager::getSurvey(size_t index) 
{
  if (index >= surveys.size()) return nullptr;
  return &surveys[index];
}