<?php
require_once __DIR__ . '/SurveyModel.php';
require_once __DIR__ . '/Question.php';

class SurveyController 
{
  private Survey $survey;

  public function __construct() // SAMPLE SURVEY
  {
    $this->survey = new Survey("Enzo's Sample Survey");

    $this->survey->addQuestion("Do you enjoy coding?", "yes/no");
    $this->survey->addQuestion("Rate your PHP skills", "rating");
    $this->survey->addQuestion("Which language do you like most?", "multiple-choice", ["C++", "Python", "JavaScript"]);
  }

  public function showForm(): void 
  {
    include __DIR__ . '/survey_form.php';
  }

  public function handleSubmission(): void 
  {
      $responses = [];
      foreach ($this->survey->questions as $i => $question) 
      {
        $field = "q$i";
        $response = $_POST[$field] ?? '';

        if (!$this->survey->validateResponse($response, $question)) 
        {
          echo "Invalid response for question " . ($i + 1);
          return;
        }

        $responses[] = $response;
      }

    $this->survey->allResponses[] = $responses;
    // $this->survey->saveResults(__DIR__ . '/../data/survey_results.txt');

    // include __DIR__ . '/../views/thank_you.php';
  }

  public function preview(): void 
  {
    $this->survey->preview();
  }

  public function results(): void 
  {
    $this->survey->viewResults();
  }

  public function dashboard() 
  {
    if ($_SESSION['role'] !== 'admin') 
    {
      echo "Access denied.";
      return;
    }
    include __DIR__ . '/admin_dashboard.php';
  }

  public function showCreateForm() 
  {
    if ($_SESSION['role'] !== 'admin') 
    {
      echo "Access denied.";
      return;
    }

    include __DIR__ . '/create_survey.php';
  }

  public function takeSurvey() 
  {
  $data = file_get_contents(__DIR__ . '/../data/surveys.json');
  $surveyArray = json_decode($data, true);

  $survey = new Survey($surveyArray['surveyName']);
  foreach ($surveyArray['questions'] as $q) 
  {
    $survey->addQuestion($q['text'], $q['type'], $q['options']);
  }

  include __DIR__ . '/survey_form.php';
}

  public function saveSurvey() // FIX LATER
  {
    if ($_SESSION['role'] !== 'admin') 
    {
      echo "Access denied.";
      return;
    }

    $surveyName = $_POST['survey_name'];
    $survey = new Survey($surveyName);

    $question = new Question($_POST['q_text'], $_POST['q_type'], explode(",", $_POST['q_options'] ?? ""));
    $survey->addQuestion($question->getText(), $question->getType(), $question->getOptions());

    file_put_contents(__DIR__ . '/../data/surveys.json', json_encode($survey));

    echo "Survey saved!";
  }
}