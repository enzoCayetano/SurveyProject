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
  bool saveSurvey(size_t index, const std::string& filename);
  bool loadSurvey(const std::string& filename);

  size_t surveyCount() const;
  Survey* getSurvey(size_t index);
};