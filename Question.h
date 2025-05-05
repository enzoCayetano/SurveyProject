#pragma once
#include <string>
#include <vector>

struct Question {
    std::string text;
    std::string type; // e.g., "open", "yes/no", "number", "multiple-choice", "rating"
    std::vector<std::string> options; // For multiple-choice questions
};