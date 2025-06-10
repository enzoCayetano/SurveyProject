<?php
  session_start();

  $_SESSION['username'] = 'admin_user';
  $_SESSION['role'] = 'admin'; // force admin for testing

  header("Location: index.php");
  exit;
?>