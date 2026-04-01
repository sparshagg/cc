# Lab 1: Lexical Analysis

This lab implements the lexical analyzer for the mini compiler using Flex.

## Objective

The lexer reads the source program from `input.txt` and classifies the input into tokens such as:

- keywords
- identifiers
- integer constants
- float constants
- arithmetic operators
- relational operators
- boolean operators
- assignment operator
- punctuation

It also reports lexical errors for unknown characters.

## Files

- `q1.l`: Flex specification for the lexical analyzer
- `input.txt`: Input source program for tokenization

## How It Works

The lexer scans characters and matches them against regular expressions.  
For each match, it prints the token category and the matched lexeme.

Example token categories:

- `KEYWORD(int)`
- `IDENTIFIER(a)`
- `INT_CONST(15)`
- `FLT_CONST(5.0)`

## How To Run

```bash
flex q1.l
gcc lex.yy.c -o lexer
./lexer
```

## Expected Output

The program prints:

- `Starting Lexical Analysis`
- token stream line by line
- `Lexical Analysis Complete`

## Viva Focus

Be ready to explain:

- what lexical analysis is
- difference between token and lexeme
- regular expressions used for identifiers and constants
- how lexical errors are detected
