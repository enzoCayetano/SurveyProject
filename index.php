<?php
  // include('db.php'); // database connection file TBA
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