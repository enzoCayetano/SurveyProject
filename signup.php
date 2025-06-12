<?php
  $errors = $_SESSION['signup_errors'] ?? [];
  $old = $_SESSION['old_input'] ?? [];

  unset($_SESSION['signup_errors'], $_SESSION['old_input']);

  include 'partials/header.php';
?>

<h2>Sign Up</h2>

<?php if (!empty($errors)): ?>
  <div class="error-box">
    <ul>
      <?php foreach ($errors as $e): ?>
        <li><?= htmlspecialchars($e) ?></li>
      <?php endforeach; ?>
    </ul>
  </div>
<?php endif; ?>

<form action="signup_handler.php" method="POST">
  <label>Username:</label><br>
  <input type="text" name="username" value="<?= htmlspecialchars($old['username'] ?? '') ?>" required><br>

  <label>Email:</label><br>
  <input type="email" name="email" value="<?= htmlspecialchars($old['email'] ?? '') ?>" required><br>

  <label>Password:</label><br>
  <input type="password" name="password" required><br>

  <label>Confirm Password:</label><br>
  <input type="password" name="confirm_password" required><br>

  <button type="submit">Sign Up</button>
</form>

<?php include 'partials/footer.php'; ?>