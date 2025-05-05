#pragma once
#include <string>
#include <vector>

struct Question 
{
    std::string text;
    std::string type;
    std::vector<std::string> options;
};