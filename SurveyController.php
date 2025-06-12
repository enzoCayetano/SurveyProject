<?php
  require_once 'SurveyModel.php';

  class SurveyController
  {
    private Survey $surveyModel;
    private PDO $pdo;

    public function __construct(PDO $pdo)
    {
      $this->pdo = $pdo;
      $this->surveyModel = new Survey($pdo);
    }

    public function dashboard(): void
    {
      $this->requireAdmin();
      include 'admin_dashboard.php';
    }

    public function showCreateForm(): void
    {
      $this->requireAdmin();
      include 'create_survey.php';
    }

    public function saveSurvey(): void
    {
      $this->requireAdmin();

      $surveyName = $_POST['survey_name'] ?? 'Untitled Survey';
      $questionText = $_POST['q_text'] ?? '';
      $questionType = $_POST['q_type'] ?? '';
      $questionOptions = isset($_POST['q_options']) ? explode(",", $_POST['q_options']) : [];

      $survey = new Survey($this->pdo, $surveyName);
      $survey->addQuestion($questionText, $questionType, $questionOptions);

      if ($survey->createSurvey()) 
      {
        echo "Survey saved successfully!";
      } 
      else 
      {
        echo "Failed to save survey.";
      }
    }

    public function takeSurvey(): void
    {
      $survey = $this->surveyModel->getLatestSurvey();
      if (!$survey) 
      {
        echo "No surveys available.";
        return;
      }

      $questions = $survey->getQuestions();
      include 'survey_form.php';
    }

    public function handleSubmission(): void
    {
      $surveyId = $_POST['survey_id'] ?? null;
      if (!$surveyId) 
      {
        echo "Invalid submission.";
        return;
      }

      $survey = Survey::loadFromDatabase($this->pdo, intval($surveyId));
      if (!$survey) 
      {
        echo "Survey not found.";
        return;
      }

      $responses = [];
      foreach ($survey->questions as $question) 
      {
        $field = "q" . $question->getId();
        $response = $_POST[$field] ?? '';
        if (!$survey->validateResponse($response, $question)) 
        {
          echo "Invalid response for question: " . htmlspecialchars($question->getText());
          return;
        }
        $responses[$question->getId()] = $response;
      }

      $userId = $_SESSION['user_id'] ?? 0;
      if (!$userId) {
        echo "User not logged in.";
        return;
      }

      if ($survey->saveResponse($userId, $responses)) 
      {
        include 'thank_you.php';
      } 
      else 
      {
        echo "Failed to save your responses.";
      }
    }

    public function results(): void
    {
      $survey = $this->surveyModel->getLatestSurvey();
      if (!$survey) 
      {
        echo "No survey found.";
        return;
      }
      $survey->viewResults();
    }

    private function requireAdmin(): void
    {
      if (!isset($_SESSION['role']) || $_SESSION['role'] !== 'admin') 
      {
        echo "Access denied.";
        exit;
      }
    }
  }
?>