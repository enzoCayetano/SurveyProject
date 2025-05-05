#include "Survey.h"
#include <iostream>
#include <algorithm>
#include <cctype>

Survey::Survey(const std::string& name) : surveyName(name) {}

bool Survey::validateResponse(const std::string& response, const Question& question) 
{
    if (question.type == "yes/no") 
    {
        return (response == "Y" || response == "N" || response == "y" || response == "n");
    } 
    else if (question.type == "number") 
    {
        return !response.empty() && std::all_of(response.begin(), response.end(), ::isdigit);
    } 
    else if (question.type == "multiple-choice") 
    {
        try 
        {
            int choice = std::stoi(response);
            return choice > 0 && choice <= static_cast<int>(question.options.size());
        } 
        catch (...) 
        {
            return false;
        }
    } 
    else if (question.type == "rating") 
    {
        try 
        {
            int rating = std::stoi(response);
            return rating >= 1 && rating <= 5; // Assuming 1-5 scale
        } 
        catch (...) 
        {
            return false;
        }
    }
    return true; // Open-ended questions accept any non-empty response
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
        bool validResponse = false;
        std::string response;

        while (!validResponse) 
        {
            std::cout << i + 1 << ". " << questions[i].text << "\n";
            if (questions[i].type == "yes/no") 
            {
                std::cout << "(Y/N): ";
            } 
            else if (questions[i].type == "number") 
            {
                std::cout << "(Enter a number): ";
            } else if (questions[i].type == "multiple-choice") 
            {
                for (size_t j = 0; j < questions[i].options.size(); ++j) 
                {
                    std::cout << j + 1 << ") " << questions[i].options[j] << "\n";
                }
                std::cout << "Enter choice (1-" << questions[i].options.size() << "): ";
            } 
            else if (questions[i].type == "rating") 
            {
                std::cout << "(Enter rating 1-5): ";
            } else {
                std::cout << "(Open-ended): ";
            }

            std::getline(std::cin, response);
            if (response.empty() && questions[i].type != "open") 
            {
                std::cout << "Sorry, the response cannot be empty. Please try again.\n";
                continue;
            }

            validResponse = validateResponse(response, questions[i]);
            if (!validResponse) 
            {
                std::cout << "Invalid input. Please try again.\n";
            } 
            else 
            {
                responses[i] = response;
            }
        }
    }

    allResponses.push_back(responses);
    std::cout << "\nSurvey completed! Thank you.\n";
}

void Survey::saveResults(const std::string& filename) 
{
    std::ofstream outFile(filename, std::ios::app);
    if (!outFile) 
    {
        std::cerr << "Error: Could not open file " << filename << ".\n";
        return;
    }

    outFile << "Survey: " << surveyName << "\n";
    for (const auto& responseSet : allResponses) 
    {
        outFile << "Response Set:\n";
        for (size_t i = 0; i < responseSet.size(); ++i) 
        {
            outFile << i + 1 << ". " << questions[i].text << ": " << responseSet[i] << "\n";
        }
        outFile << "\n";
    }
    outFile.close();
    std::cout << "Results saved to " << filename << "\n";
}

bool Survey::loadFromFile(const std::string& filename) 
{
    std::ifstream inFile(filename);
    if (!inFile) 
    {
        std::cerr << "Error: Could not open file " << filename << " for reading.\n";
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
            std::getline(inFile, line); // Read type
            std::string type = line.substr(6); // "Type: "
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
        std::cout << "No responses recorded for " << surveyName << ".\n";
        return;
    }

    std::cout << "\n=== Results for " << surveyName << " ===\n";
    for (size_t set = 0; set < allResponses.size(); ++set) 
    {
        std::cout << "\nResponse Set " << set + 1 << ":\n";
        for (size_t i = 0; i < allResponses[set].size(); ++i) 
        {
            std::cout << i + 1 << ". " << questions[i].text << ": " << allResponses[set][i] << "\n";
        }
    }
}