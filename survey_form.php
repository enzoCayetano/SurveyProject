<form action="?action=submit" method="POST">
  <?php foreach ($survey->questions as $i => $q): ?>
    <p><?= ($i + 1) ?>. <?= htmlspecialchars($q->getText()) ?></p>

    <?php if ($q->getType() === "multiple-choice"): ?>
      <?php foreach ($q->getOptions() as $j => $opt): ?>
        <label>
          <input type="radio" name="q<?= $i ?>" value="<?= $j + 1 ?>"> <?= htmlspecialchars($opt) ?>
        </label><br>
      <?php endforeach; ?>

    <?php elseif ($q->getType() === "yes/no"): ?>
      <input type="radio" name="q<?= $i ?>" value="Y"> Yes
      <input type="radio" name="q<?= $i ?>" value="N"> No

    <?php elseif ($q->getType() === "rating"): ?>
      <input type="number" name="q<?= $i ?>" min="1" max="5">

    <?php else: ?>
      <input type="text" name="q<?= $i ?>">
    <?php endif; ?>

  <?php endforeach; ?>

  <br><input type="submit" value="Submit">
</form>
