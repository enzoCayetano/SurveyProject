#include "Question.h"

Question::Question(const std::string& text, const std::string& type, const std::vector<std::string>& options)
 : text(text), type(type), options(options) {}

const std::string& Question::getText() const
{
  return text;
}

const std::string& Question::getType() const
{
  return type;
}

const std::vector<std::string>& Question::getOptions() const
{
  return options;
}