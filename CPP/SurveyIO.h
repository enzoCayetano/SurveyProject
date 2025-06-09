#pragma once

#include <string>
#include "Survey.h"

namespace SurveyIO
{
  bool saveSurvey(const Survey& survey, const std::string& filename);
  bool loadSurvey(Survey& survey, const std::string& filename);
}