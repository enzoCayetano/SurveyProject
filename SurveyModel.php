<?php
  require_once 'Question.php';

  class Survey
  {
    private PDO $pdo;
    public int $id;
    public string $surveyName;
    public array $questions = [];

    public function __construct(PDO $pdo, string $name = "", int $id = 0)
    {
      $this->pdo = $pdo;
      $this->surveyName = $name;
      $this->id = $id;
    }

    public function addQuestion(string $text, string $type, array $options = []): void
    {
      $this->questions[] = new Question($text, $type, $options);
    }

    public function createSurvey(): bool
    {
      try 
      {
        $this->pdo->beginTransaction();

        $stmt = $this->pdo->prepare("INSERT INTO surveys (survey_name) VALUES (?)");
        $stmt->execute([$this->surveyName]);
        $this->id = $this->pdo->lastInsertId();

        foreach ($this->questions as $q) 
        {
          $stmtQ = $this->pdo->prepare("INSERT INTO questions (survey_id, question_text, question_type, options) VALUES (?, ?, ?, ?)");
          $optionsJson = $q->getOptions() ? json_encode($q->getOptions()) : null;
          $stmtQ->execute([$this->id, $q->getText(), $q->getType(), $optionsJson]);
          $q->setId($this->pdo->lastInsertId());
        }

        $this->pdo->commit();
        return true;
      } 
      catch (PDOException $e) 
      {
        $this->pdo->rollBack();
        error_log("Survey creation failed: " . $e->getMessage());
        return false;
      }
    }

    public static function loadFromDatabase(PDO $pdo, int $surveyId): ?Survey
    {
      $stmt = $pdo->prepare("SELECT * FROM surveys WHERE id = ?");
      $stmt->execute([$surveyId]);
      $surveyData = $stmt->fetch(PDO::FETCH_ASSOC);

      if (!$surveyData) return null;

      $survey = new Survey($pdo, $surveyData['survey_name'], $surveyId);

      $qstmt = $pdo->prepare("SELECT * FROM questions WHERE survey_id = ?");
      $qstmt->execute([$surveyId]);
      while ($q = $qstmt->fetch(PDO::FETCH_ASSOC)) 
      {
        $options = $q['options'] ? json_decode($q['options'], true) : [];
        $survey->questions[] = new Question($q['question_text'], $q['question_type'], $options, $q['id']);
      }

      return $survey;
    }

    public function getLatestSurvey(): ?Survey
    {
      $stmt = $this->pdo->query("SELECT id FROM surveys ORDER BY id DESC LIMIT 1");
      $row = $stmt->fetch(PDO::FETCH_ASSOC);
      if (!$row) return null;
      return self::loadFromDatabase($this->pdo, intval($row['id']));
    }

    public function getQuestions(): array
    {
      return $this->questions;
    }

    public function saveResponse(int $userId, array $responses): bool
    {
      try 
      {
        $this->pdo->beginTransaction();

        $stmt = $this->pdo->prepare("INSERT INTO responses (survey_id, user_id, submitted_at) VALUES (?, ?, NOW())");
        $stmt->execute([$this->id, $userId]);
        $responseId = $this->pdo->lastInsertId();

        foreach ($this->questions as $question) 
        {
          $answer = $responses[$question->getId()] ?? '';
          $ansStmt = $this->pdo->prepare("INSERT INTO answers (response_id, question_id, answer) VALUES (?, ?, ?)");
          $ansStmt->execute([$responseId, $question->getId(), $answer]);
        }

        $this->pdo->commit();
        return true;
      } 
      catch (PDOException $e) 
      {
        $this->pdo->rollBack();
        error_log("Error saving response: " . $e->getMessage());
        return false;
      }
    }

    public function validateResponse(string $response, Question $question): bool
    {
      $type = $question->getType();
      if ($type === "yes/no") 
      {
        return in_array(strtolower($response), ["y", "n"]);
      } 
      elseif ($type === "number") 
      {
        return is_numeric($response);
      } 
      elseif ($type === "multiple-choice") 
      {
        return in_array($response, $question->getOptions());
      } 
      elseif ($type === "rating") 
      {
        $rating = intval($response);
        return $rating >= 1 && $rating <= 5;
      }
      return true;
    }

    public function viewResults(): void
    {
      echo "<h2>Results for " . htmlspecialchars($this->surveyName) . "</h2>";

      foreach ($this->questions as $q) 
      {
        echo "<h3>" . htmlspecialchars($q->getText()) . "</h3>";

        $stmt = $this->pdo->prepare("
          SELECT answer, COUNT(*) as count 
          FROM answers 
          WHERE question_id = ? 
          GROUP BY answer
        ");
        $stmt->execute([$q->getId()]);
        $results = $stmt->fetchAll(PDO::FETCH_ASSOC);

        if (empty($results)) 
        {
          echo "<p>No responses.</p>";
        } 
        else 
        {
          echo "<ul>";
          foreach ($results as $r) 
          {
            echo "<li>" . htmlspecialchars($r['answer']) . ": " . $r['count'] . "</li>";
          }
          echo "</ul>";
        }
      }
    }
  }
?>