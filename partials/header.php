<?php 
  if (session_status() === PHP_SESSION_NONE) 
  {
    session_start();
  }

  if (!isset($_SESSION['username']) && isset($_COOKIE['remember_token'])) 
  {
    require_once 'db.php';
    $stmt = $pdo->prepare("SELECT * FROM users WHERE remember_token = ?");
    $stmt->execute([$_COOKIE['remember_token']]);
    $user = $stmt->fetch(PDO::FETCH_ASSOC);

    if ($user) 
    {
      $_SESSION['username'] = $user['username'];
      $_SESSION['role'] = $user['role'] ?? 'user';
    }
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
        <li><a href="survey.php?action=take">Take Survey</a></li>

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