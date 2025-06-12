<?php 
  include 'partials/header.php'; 
  require 'db.php';

  if (!isset($_SESSION['username']) && isset($_COOKIE['remember_token'])) 
  {
    $token = $_COOKIE['remember_token'];

    $stmt = $pdo->prepare("SELECT * FROM users WHERE remember_token = ?");
    $stmt->execute([$token]);
    $user = $stmt->fetch(PDO::FETCH_ASSOC);

    if ($user) 
    {
      $_SESSION['username'] = $user['username'];
      $_SESSION['role'] = 'user';
    }
  }
?>

<h1>Welcome to Enzo's Survey Project</h1>
<a href="login.php" class="button">Log In</a>
<a href="signup.php" class="button">Sign Up</a>

<?php include 'partials/footer.php'; ?>