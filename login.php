<?php
  session_start();
  $errors = $_SESSION['login_errors'] ?? [];
  unset($_SESSION['login_errors']);

  include 'partials/header.php';
?>

<h2>Login</h2>

<?php if (!empty($errors)): ?>
  <div class="error-box">
    <ul>
      <?php foreach ($errors as $e): ?>
        <li><?= htmlspecialchars($e) ?></li>
      <?php endforeach; ?>
    </ul>
  </div>
<?php endif; ?>

<form action="login_handler.php" method="POST">
  <label>Username or Email:</label><br>
  <input type="text" name="login" required><br>

  <label>Password:</label><br>
  <input type="password" name="password" required><br>
  
  <label><input type="checkbox" name="remember"> Remember me</label>

  <button type="submit">Login</button>
</form>

<?php include 'partials/footer.php'; ?>
