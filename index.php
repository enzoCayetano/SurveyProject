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
<!DOCTYPE html>
<html>
  <head>
    <title>Enzo's Survey Project</title>
    <link rel="stylesheet" href="/styles.css">
  </head>
  <body>
    <header>
      <nav>
        <ul>
          <li><a href="index.php">Home</a></li>
          <li><a href="survey.php">Take Survey</a></li>
          <li><a href="results.php">View Results</a></li>
        </ul>
      </nav>
    </header>
    <main>
      <h1>Welcome to Enzo's Survey Project</h1>
      <a href="login.php" class="button">Log In</a>
      <a href="signup.php" class="button">Sign Up</a>
    </main>
  </body>
  <footer>
    <p>&copy; <?php echo date("Y"); ?> Enzo Cayetano. All rights reserved.</p>
  </footer>
</html>