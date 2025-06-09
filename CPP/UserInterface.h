#pragma once

#include "SurveyManager.h"

class UserInterface
{
public:
  UserInterface();

  void executeInterface();

private:
  SurveyManager manager;

  void userPanel();
  void adminPanel();
  void loginMenu();
};