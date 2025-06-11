<?php include 'partials/header.php'; ?>

<h2>Create a New Survey</h2>
<form method="POST" action="?action=save">
  Survey Name: <input type="text" name="survey_name" required><br><br>

  Question Text: <input type="text" name="q_text" required><br>
  Question Type:
  <select name="q_type">
    <option value="yes/no">Yes/No</option>
    <option value="number">Number</option>
    <option value="multiple-choice">Multiple Choice</option>
    <option value="rating">Rating</option>
  </select><br>
  Options (comma-separated, if multiple-choice): <input type="text" name="q_options"><br>

  <input type="submit" value="Save Survey">
  
<?php include 'partials/footer.php'; ?>