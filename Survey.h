#pragma once
#include "Question.h"
#include <string>
#include <vector>
#include <fstream>

class Survey 
{
private:
    std::string surveyName;
    std::vector<Question> questions;
    std::vector<std::vector<std::string>> allResponses;

    bool validateResponse(const std::string& response, const Question& question);

public:
    Survey(const std::string& name);

    void addQuestion(const std::string& text, const std::string& type = "open", const std::vector<std::string>& options = {});
    void conductSurvey();
    void preview() const;
    void saveResults(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    void viewResults() const;

    std::string getName() const { return surveyName; }
    size_t getQuestionCount() const { return questions.size(); }
};