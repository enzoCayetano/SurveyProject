<?php
  session_start();
  require 'db.php';

  if (isset($_SESSION['username']))
  {
    $stmt = $pdo->prepare("UPDATE users SET remember_token = NULL WHERE username = ?");
    $stmt->execute([$_SESSION['username']]);
  }

  setcookie('remember_token', '', time() - 3600, "/");
  session_destroy();

  header("Location: login.php");
  exit;
?>