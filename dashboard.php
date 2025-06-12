<?php
  include 'partials/header.php';

  if (!isset($_SESSION['user'])) {
    header("Location: login.php");
    exit;
  }

  echo "<h1>Welcome, " . htmlspecialchars($_SESSION['user']) . "!</h1>";
  echo '<a href="logout.php">Logout</a>';

  include 'partials/footer.php';
?>