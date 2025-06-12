<?php
  session_start();
  require 'db.php';

  $login = trim($_POST['login'] ?? '');
  $password = $_POST['password'] ?? '';
  $errors = [];

  $stmt = $pdo->prepare("SELECT * FROM users WHERE username = ? OR email = ?");
  $stmt->execute([$login, $login]);
  $user = $stmt->fetch(PDO::FETCH_ASSOC);

  if ($user && password_verify($password, $user['password_hash'])) 
  {
    $_SESSION['user'] = $user['username'];
    header("Location: dashboard.php");
    exit;
  } 
  else 
  {
    $errors[] = "Invalid credentials.";
    $_SESSION['login_errors'] = $errors;
    header("Location: login.php");
    exit;
  }
?>