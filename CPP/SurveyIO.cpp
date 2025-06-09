#include <fstream>
#include "SurveyIO.h"

bool SurveyIO::saveSurvey(const Survey& survey, const std::string& filename)
{
  std::ofstream out(filename, std::ios::binary);
  if (!out) return false;

  size_t nameLen = survey.getName().size();
  out.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
  out.write(survey.getName().c_str(), nameLen);

  const auto& questions = survey.getQuestions();
  size_t qCount = questions.size();
  out.write(reinterpret_cast<const char*>(&qCount), sizeof(qCount));

  for (const auto& q : questions) 
  {
    size_t textLen = q.getText().size();
    out.write(reinterpret_cast<const char*>(&textLen), sizeof(textLen));
    out.write(q.getText().c_str(), textLen);

    size_t typeLen = q.getType().size();
    out.write(reinterpret_cast<const char*>(&typeLen), sizeof(typeLen));
    out.write(q.getType().c_str(), typeLen);

    const auto& options = q.getOptions();
    size_t optCount = options.size();
    out.write(reinterpret_cast<const char*>(&optCount), sizeof(optCount));
    for (const std::string& opt : options) 
    {
      size_t optLen = opt.size();
      out.write(reinterpret_cast<const char*>(&optLen), sizeof(optLen));
      out.write(opt.c_str(), optLen);
    }
  }

  return true;
}

bool SurveyIO::loadSurvey(Survey& survey, const std::string& filename)
{
  std::ifstream in(filename, std::ios::binary);
  if (!in) return false;

  size_t nameLen;
  in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
  std::string name(nameLen, '\0');
  in.read(&name[0], nameLen);

  survey.setName(name);

  size_t qCount;
  in.read(reinterpret_cast<char*>(&qCount), sizeof(qCount));
  for (size_t i = 0; i < qCount; ++i) 
  {
    size_t textLen;
    in.read(reinterpret_cast<char*>(&textLen), sizeof(textLen));
    std::string text(textLen, '\0');
    in.read(&text[0], textLen);

    size_t typeLen;
    in.read(reinterpret_cast<char*>(&typeLen), sizeof(typeLen));
    std::string type(typeLen, '\0');
    in.read(&type[0], typeLen);

    size_t optCount;
    in.read(reinterpret_cast<char*>(&optCount), sizeof(optCount));
    std::vector<std::string> options;
    for (size_t j = 0; j < optCount; ++j) 
    {
      size_t optLen;
      in.read(reinterpret_cast<char*>(&optLen), sizeof(optLen));
      std::string opt(optLen, '\0');
      in.read(&opt[0], optLen);
      options.push_back(opt);
    }

    survey.addQuestion(text, type, options);
  }
  
  return true;
}