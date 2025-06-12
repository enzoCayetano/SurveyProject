<?php
  session_start();
  header("Cache-Control: no-store, no-cache, must-revalidate");
  require 'db.php';

  $login = trim($_POST['login'] ?? '');
  $password = $_POST['password'] ?? '';
  $remember = isset($_POST['remember']);
  $errors = [];

  $stmt = $pdo->prepare("SELECT * FROM users WHERE username = ? OR email = ?");
  $stmt->execute([$login, $login]);
  $user = $stmt->fetch(PDO::FETCH_ASSOC);

  if ($user && password_verify($password, $user['password_hash'])) 
  {
    $_SESSION['username'] = $user['username'];
    $_SESSION['role'] = $user['role'] ?? 'user';

    if ($remember) 
    {
      $token = bin2hex(random_bytes(16));
      $stmt = $pdo->prepare("UPDATE users SET remember_token = ? WHERE id = ?");
      $stmt->execute([$token, $user['id']]);
      setcookie('remember_token', $token, time() + (86400 * 30), "/");
    }

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
