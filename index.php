<?php 
  session_start(); 
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
          <li><a href="survey.php?action=take">Take Survey</a></li>
          <li><a href="survey.php?action=results">View Results</a></li>

          <?php if (isset($_SESSION['role']) && $_SESSION['role'] === 'admin'): ?>
            <li><a href="survey.php?action=dashboard">Admin Dashboard</a></li>
          <?php endif; ?>

          <?php if (isset($_SESSION['username'])): ?>
            <li><a href="logout.php">Log Out (<?= htmlspecialchars($_SESSION['username']) ?>)</a></li>
          <?php else: ?>
            <li><a href="login.php">Log In</a></li>
            <li><a href="signup.php">Sign Up</a></li>
          <?php endif; ?>
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