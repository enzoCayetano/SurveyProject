<?php
  if (session_status() === PHP_SESSION_NONE) 
  {
    session_start();
  }
  
  require_once 'SurveyController.php';
  require_once 'db.php';

  $controller = new SurveyController($pdo);

  $action = $_GET['action'] ?? ((isset($_SESSION['role']) && $_SESSION['role'] === 'admin') ? 'dashboard' : 'take');

  switch ($action) 
  {
    case 'dashboard': $controller->dashboard(); break;
    case 'create': $controller->showCreateForm(); break;
    case 'save': $controller->saveSurvey(); break;
    case 'take': $controller->takeSurvey(); break;
    case 'submit': $controller->handleSubmission(); break;
    case 'results': $controller->results(); break;
    default: echo "404 Not Found";
  }
?>