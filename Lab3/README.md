# Lab 3: Syntax Error Detection and Semantic Extension

This lab extends the parser from Lab 2 by improving error reporting and adding semantic-analysis checks.

## Objective

The main goal of this lab is to detect and report syntax errors more clearly instead of only stopping at the first invalid construct.

In addition, this lab includes semantic-analysis logic as an extension.

## Files

- `lex.l`: Lexer used by the parser
- `par.y`: Parser grammar with syntax-error handling and semantic checks
- `parser_types.h`: Shared type definitions for semantic values
- `input.txt`: Sample input program

## Syntax Error Handling

The parser reports targeted syntax errors such as:

- missing `;` after declaration or assignment
- missing `=` in assignment
- missing `)` after `if` or `while` condition
- missing braces around blocks
- missing expression inside `print` or `printf`

## Semantic Checks Included

This lab also checks:

- use of undeclared identifiers
- redeclaration of identifiers
- type mismatch in assignment
- invalid operand types in expressions
- invalid conditions in `if` and `while`

## How To Run

```bash
bison -d par.y
flex lex.l
gcc par.tab.c lex.yy.c -o parser
./parser
```

## Example Use

You can modify `input.txt` to test valid and invalid cases, then rerun the parser.

Example syntax-error cases:

- `int a; a 5;`
- `while (a < 5 { a = a + 1; }`

## Viva Focus

Be ready to explain:

- difference between syntax error and semantic error
- how parser recovery rules improve error reporting
- examples of specific syntax errors detected by the parser
- which semantic checks were added as an extension
