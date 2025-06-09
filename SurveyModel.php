<?php

require_once 'Question.php';

class Survey 
{
  public string $surveyName;
  public array $questions = [];
  public array $allResponses = [];

  public function __construct(string $name = "") 
  {
    $this->surveyName = $name;
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
      $choice = intval($response);
      return $choice > 0 && $choice <= count($question->getOptions());
    } 
    elseif ($type === "rating") 
    {
      $rating = intval($response);
      return $rating >= 1 && $rating <= 5;
    }

    return true;
  }

  public function addQuestion(string $text, string $type, array $options = []): void 
  {
    $this->questions[] = new Question($text, $type, $options);
  }

  public function conductSurvey(): void 
  {
    echo "<h2>" . htmlspecialchars($this->surveyName) . " Survey</h2>";
    $responses = [];

    foreach ($this->questions as $i => $q) 
    {
      $prompt = "<p>" . ($i + 1) . ". " . htmlspecialchars($q->getText()) . "</p>";

      if ($q->getType() === "multiple-choice") 
      {
        foreach ($q->getOptions() as $j => $opt) 
        {
          $prompt .= "<div>" . ($j + 1) . ") " . htmlspecialchars($opt) . "</div>";
        }
      }

      echo $prompt;
    }
  }

  public function preview(): void 
  {
    echo "<h3>Survey Preview: " . htmlspecialchars($this->surveyName) . "</h3>";
    foreach ($this->questions as $i => $q) 
    {
      echo "<p>" . ($i + 1) . ". " . htmlspecialchars($q->getText()) . " [" . $q->getType() . "]</p>";
      if ($q->getType() === "multiple-choice") 
      {
        foreach ($q->getOptions() as $opt) 
        {
          echo "<div>&nbsp;&nbsp;- " . htmlspecialchars($opt) . "</div>";
        }
      }
    }
  }

  public function saveResults(string $filename): void {
    $file = fopen($filename, "a");
    if (!$file) 
    {
      echo "Error: Could not open file for writing.<br>";
      return;
    }

    fwrite($file, "Survey: " . $this->surveyName . "\n");
    foreach ($this->allResponses as $responseSet) 
    {
      fwrite($file, "Response Set:\n");
      foreach ($responseSet as $i => $response) 
      {
        fwrite($file, ($i + 1) . ". " . $this->questions[$i]->getText() . ": " . $response . "\n");
      }
      fwrite($file, "\n");
    }

    fclose($file);
    echo "Results saved to $filename<br>";
  }

  public function loadFromFile(string $filename): bool 
  {
    if (!file_exists($filename)) 
    {
      echo "Error: File not found.<br>";
      return false;
    }

    $lines = file($filename, FILE_IGNORE_NEW_LINES);
    $this->questions = [];
    $this->allResponses = [];

    foreach ($lines as $line) 
    {
      if (str_starts_with($line, "Survey: ")) 
      {
        $this->surveyName = substr($line, 8);
      } 
      elseif (str_starts_with($line, "Question: ")) 
      {
        $text = substr($line, 10);
        $type = trim(next($lines));
        $this->questions[] = new Question($text, $type);
      }
    }

    return true;
  }

  public function viewResults(): void 
  {
    if (empty($this->allResponses)) 
    {
      echo "<p>No responses recorded for " . htmlspecialchars($this->surveyName) . ".</p>";
      return;
    }

    echo "<h2>Results for " . htmlspecialchars($this->surveyName) . "</h2>";
    foreach ($this->allResponses as $setIndex => $responseSet) 
    {
      echo "<h4>Response Set " . ($setIndex + 1) . "</h4>";
      foreach ($responseSet as $i => $response) 
      {
        echo "<p>" . ($i + 1) . ". " . $this->questions[$i]->getText() . ": " . htmlspecialchars($response) . "</p>";
      }
    }
  }
}
