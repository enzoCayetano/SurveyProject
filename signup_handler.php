<?php
session_start();
require 'db.php';

$username = trim($_POST['username']);
$email = trim($_POST['email']);
$password = $_POST['password'];
$confirm = $_POST['confirm_password'];

$errors = [];

if (!preg_match("/^[a-zA-Z0-9_]{3,20}$/", $username)) 
{
  $errors[] = "Username must be 3-20 characters and contain only letters, numbers, or underscores.";
}

if (!preg_match("/^[\w\-\.]+@([\w-]+\.)+[\w-]{2,4}$/", $email)) 
{
  $errors[] = "Invalid email format.";
}

if (!preg_match("/^(?=.*[A-Z])(?=.*[a-z])(?=.*\d)(?=.*[\W_]).{8,}$/", $password)) 
{
  $errors[] = "Password must be at least 8 characters with upper, lower, digit, and special char.";
}

if ($password !== $confirm) 
{
  $errors[] = "Passwords do not match.";
}

if (empty($errors)) 
{
  try 
  {
    $stmt = $pdo->prepare("SELECT id FROM users WHERE username = ? OR email = ?");
    $stmt->execute([$username, $email]);
    if ($stmt->fetch()) 
    {
      $errors[] = "Username or email already taken.";
    }
  } 
  catch (PDOException $e) 
  {
    $errors[] = "Database error: " . $e->getMessage();
  }
}

if (!empty($errors)) 
{
  $_SESSION['signup_errors'] = $errors;
  $_SESSION['old_input'] = ['username' => $username, 'email' => $email];
  header("Location: signup.php");
  exit;
}

$hash = password_hash($password, PASSWORD_DEFAULT);

try 
{
  $stmt = $pdo->prepare("INSERT INTO users (username, email, password_hash) VALUES (?, ?, ?)");
  $stmt->execute([$username, $email, $hash]);

  $_SESSION['username'] = $username;
  $_SESSION['role'] = 'user';

  if (!empty($_POST['remember'])) 
  {
    $token = bin2hex(random_bytes(32));
    setcookie('remember_token', $token, time() + (86400 * 30), "/");
    
    // Store token in DB
    $stmt = $pdo->prepare("UPDATE users SET remember_token = ? WHERE username = ?");
    $stmt->execute([$token, $username]);
  }

  header("Location: index.php");
  exit;
} 
catch (PDOException $e) 
{
  $_SESSION['signup_errors'] = ["Database insert error: " . $e->getMessage()];
  $_SESSION['old_input'] = ['username' => $username, 'email' => $email];
  header("Location: signup.php");
  exit;
}