#pragma once
#include <string>
#include <vector>

struct Question 
{
private:
    std::string text;
    std::string type;
    std::vector<std::string> options;

public:
    Question(const std::string& text, const std::string& type, const std::vector<std::string>& options = {});

    const std::string& getText() const;
    const std::string& getType() const;
    const std::vector<std::string>& getOptions() const;
};