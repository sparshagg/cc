# Lab 6: Intermediate Code Generation

This lab extends the compiler pipeline by generating Three-Address Code (TAC) after parsing and semantic analysis.

It corresponds to the evaluation phase for:

- Question 4: Intermediate Code Generation

## Objective

The compiler now generates TAC in a structured representation for the prescribed evaluation program.

This implementation uses:

- quadruples

It handles:

- arithmetic expressions
- boolean expressions
- assignments
- `if`
- `if-else`
- `while`
- temporary variables
- labels and jumps for control flow

## Files

- `main.py`: build-and-run driver for the full pipeline
- `par.y`: parser with semantic actions and AST generation
- `lex.l`: lexer
- `symtab.c`: symbol table implementation
- `symtab.h`: symbol table interface
- `tac.c`: TAC generation logic
- `tac.h`: quadruple structure and TAC interface
- `input.txt`: input program
- `quadruples.txt`: generated TAC output
- `errors.txt`: generated error log
- `symbol_table.txt`: generated symbol table snapshot
- `tree_output.txt`: generated AST output
- `trace_output.txt`: generated parser trace
- `ll1_theory_output.txt`: generated FIRST/FOLLOW and LL(1) theory output
- `Makefile`: optional build file

## Implementation Summary

### Pipeline

Lab 6 builds on top of the previous phases:

1. lexical analysis
2. parsing
3. symbol table handling
4. semantic analysis
5. TAC generation

TAC is only produced when syntax and semantic analysis succeed.

### Quadruple Representation

The TAC representation is defined in `tac.h` using:

- operator
- argument 1
- argument 2
- result

### TAC Generation

The generator in `tac.c` traverses the AST and emits quadruples.

It creates:

- temporaries using `new_temp()`
- labels using `new_label()`
- TAC instructions using `emit()`

Control flow is represented explicitly with:

- `LABEL`
- `GOTO`
- `IFFALSE`

## How To Run

Recommended command:

```bash
python3 main.py
```

The driver:

1. builds the compiler
2. runs parsing and semantic analysis
3. generates TAC
4. writes all output files

## Expected Outputs

After running, check:

- `quadruples.txt`
- `errors.txt`
- `symbol_table.txt`
- `tree_output.txt`
- `trace_output.txt`
- `ll1_theory_output.txt`

## Viva Focus

Be ready to explain:

- why quadruples were chosen
- how expressions are translated into TAC
- how temporaries are created
- how `if`, `if-else`, and `while` are translated
- how labels and jumps represent control flow
- how TAC is generated from the AST, not hardcoded
