<?php
  session_start();
  require_once __DIR__ . '/SurveyController.php';

  $controller = new SurveyController();

  $action = $_GET['action'] ?? ($_SESSION['role'] === 'admin' ? 'dashboard' : 'take');


  switch ($action) {
    case 'dashboard': $controller->dashboard(); break;
    case 'create': $controller->showCreateForm(); break;
    case 'save': $controller->saveSurvey(); break;
    case 'take': $controller->takeSurvey(); break;
    case 'submit': $controller->handleSubmission(); break;
    case 'results': $controller->results(); break;
    default: echo "404 Not Found";
  }
?>