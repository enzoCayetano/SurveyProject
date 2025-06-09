#pragma once

#include <vector>
#include <string>
#include "Survey.h"

class SurveyManager 
{
private:
  std::vector<Survey> surveys;

public:
  void addSurvey(const Survey& survey);
  void listSurveys() const;

  size_t surveyCount() const;
  Survey* getSurvey(size_t index);
};