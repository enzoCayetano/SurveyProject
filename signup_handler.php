<?php
session_start();

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

if ($password !== $confirm) {
  $errors[] = "Passwords do not match.";
}

if (!empty($errors)) {
  $_SESSION['signup_errors'] = $errors;
  $_SESSION['old_input'] = ['username' => $username, 'email' => $email];
  header("Location: signup.php");
  exit;
}

$_SESSION['username'] = $username;
$_SESSION['role'] = 'user';

header("Location: index.php");
exit;