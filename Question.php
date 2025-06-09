<?php

class Question 
{
    private string $text;
    private string $type;
    private array $options;

    public function __construct(string $text, string $type, array $options = []) 
    {
        $this->text = $text;
        $this->type = $type;
        $this->options = $options;
    }

    public function getText(): string 
    {
        return $this->text;
    }

    public function getType(): string 
    {
        return $this->type;
    }

    public function getOptions(): array 
    {
        return $this->options;
    }
}