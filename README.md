# Compiler Construction Lab

This repository contains the first seven labs completed for the Compiler Construction assignment:

- `Lab1`: Lexical analysis
- `Lab2`: CFG-based syntax analysis
- `Lab3`: Syntax error detection and semantic-analysis extension
- `Lab4`: Parser implementation using Shift-Reduce and LL(1)
- `Lab5`: Symbol table, scope handling, and semantic analysis
- `Lab6`: Intermediate code generation using TAC (quadruples)
- `Lab7`: Optimization and target code generation

The labs build on each other:

1. `Lab1` tokenizes the input source program.
2. `Lab2` uses a lexer and parser to validate syntax and print a parse tree with derivations.
3. `Lab3` improves syntax-error reporting and adds semantic checks as an extension.
4. `Lab4` upgrades syntax analysis into algorithmic parser construction and demonstrates two parsing techniques.
5. `Lab5` adds symbol table management, scope handling, and semantic validation on top of parsing.
6. `Lab6` generates intermediate code in TAC form from the AST after successful parsing and semantic checking.
7. `Lab7` optimizes the generated TAC and emits target pseudo assembly to complete the compiler pipeline.

## Repository Structure

### `Lab1/`

- `q1.l`: Flex specification for the lexer
- `input.txt`: Input program for Lab 1

### `Lab2/`

- `lex.l`: Flex lexer for parser input
- `par.y`: Bison grammar for syntax analysis
- `input.txt`: Official evaluation program used for syntax validation

### `Lab3/`

- `lex.l`: Flex lexer with extra tracking for error reporting
- `par.y`: Bison grammar with syntax-error handling and semantic checks
- `parser_types.h`: Shared semantic value and type definitions
- `input.txt`: Sample input for Lab 3

### `Lab4/`

- `lex.l`: Flex lexer for the shift-reduce parser
- `par.y`: Bison grammar for shift-reduce parsing
- `ll1.py`: LL(1) parser with FIRST/FOLLOW computation and stack trace
- `input.txt`: Evaluation program used by both parser implementations

### `Lab5/`

- `main.py`: Driver that builds and runs the parser, semantic analyzer, and LL(1) theory output
- `par.y`: Parser with semantic actions
- `symtab.c`: Symbol table implementation with scope and offset handling
- `symtab.h`: Symbol table interface
- `input.txt`: Evaluation program used for semantic analysis

### `Lab6/`

- `main.py`: Driver that builds and runs the full compiler pipeline
- `par.y`: Parser with semantic actions and TAC generation
- `symtab.c`: Symbol table implementation
- `tac.c`: TAC generation logic
- `tac.h`: TAC interface and quadruple structure
- `input.txt`: Evaluation program used for TAC generation

### `Lab7/`

- `main.py`: Driver that builds and runs the full compiler pipeline with optimization and target code generation
- `par.y`: Parser with semantic actions, TAC, optimization, and codegen integration
- `symtab.c`: Symbol table implementation
- `tac.c`: TAC, optimization, and target-code-generation logic
- `tac.h`: TAC interface and optimization/codegen declarations
- `input.txt`: Evaluation program used for optimization and target code generation

## Prerequisites

The following tools should be installed:

- `flex`
- `bison`
- `gcc`
- `python3`

Check them with:

```bash
which flex
which bison
which gcc
which python3
```

## How To Run

### Lab 1

```bash
cd Lab1
flex q1.l
gcc lex.yy.c -o lexer
./lexer
```

### Lab 2

```bash
cd Lab2
bison -d par.y
flex lex.l
gcc par.tab.c lex.yy.c -o parser
./parser
```

### Lab 3

```bash
cd Lab3
bison -d par.y
flex lex.l
gcc par.tab.c lex.yy.c -o parser
./parser
```

### Lab 4

Shift-reduce parser:

```bash
cd Lab4
bison -d -t par.y
flex lex.l
gcc par.tab.c lex.yy.c -o parser
./parser
```

LL(1) parser:

```bash
cd Lab4
python3 ll1.py
```

### Lab 5

Recommended driver:

```bash
cd Lab5
python3 main.py
```

### Lab 6

Recommended driver:

```bash
cd Lab6
python3 main.py
```

### Lab 7

Recommended driver:

```bash
cd Lab7
python3 main.py
```

## Notes

- Run each lab from inside its own directory because the programs read `input.txt` from the current working directory.
- `Lab4`, `Lab5`, `Lab6`, and `Lab7` read from `input.txt`.
- On this machine, the commands above work without linking `-lfl`.
- `python3` is required for the driver scripts used in `Lab4` through `Lab7`.
- `Lab2` is the main midsem syntax-analysis demo because it parses the official evaluation program.
- `Lab3` is useful for showing syntax-error reporting and the semantic-analysis extension.
- `Lab4` is the parser-implementation phase and demonstrates both shift-reduce and LL(1) parsing.
- `Lab5` is the symbol-table and semantic-analysis phase.
- `Lab6` is the intermediate-code-generation phase and emits TAC in quadruple form.
- `Lab7` is the optimization and target-code-generation phase, showing TAC before/after optimization and pseudo assembly output.
- In `Lab6` and `Lab7`, most compiler results are printed to the console during execution; some text artifacts in those folders are committed sample outputs from earlier runs.
