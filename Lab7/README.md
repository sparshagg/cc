# Lab 7: Optimization and Target Code Generation

This lab completes the compiler pipeline by extending intermediate code generation with:

- code optimization
- target code generation

It corresponds to the evaluation phase for:

- Question 5: Optimization and Target Code Generation

## Objective

The compiler now:

- generates TAC in quadruple form
- applies a basic optimization technique
- generates target pseudo assembly

This lab demonstrates:

- TAC before optimization
- TAC after optimization
- target code generation from the intermediate representation
- preservation of control flow using labels and jumps

## Files

- `main.py`: build-and-run driver for the full pipeline
- `par.y`: parser with semantic actions and AST generation
- `lex.l`: lexer
- `symtab.c`: symbol table implementation
- `symtab.h`: symbol table interface
- `tac.c`: TAC generation, optimization, and target code generation
- `tac.h`: TAC interface and quadruple declarations
- `input.txt`: input program
- `quadruples.txt`: generated TAC output
- `optimized_quads.txt`: generated optimized TAC output
- `target_code.asm`: generated target code output
- `errors.txt`: generated error log
- `symbol_table.txt`: generated symbol table snapshot
- `tree_output.txt`: generated AST output
- `trace_output.txt`: generated parser trace
- `ll1_theory_output.txt`: generated FIRST/FOLLOW and LL(1) theory output
- `Makefile`: optional build file

## Implementation Summary

### Full Pipeline

Lab 7 builds on top of all earlier phases:

1. lexical analysis
2. parsing
3. symbol table handling
4. semantic analysis
5. TAC generation
6. optimization
7. target code generation

### Optimization

The optimization logic is implemented in `tac.c`.

Current optimization:

- constant folding

It scans TAC instructions and, when both operands are numeric constants, computes the result at compile time and rewrites the quadruple into a direct assignment.

### Target Code Generation

The target code generator is also implemented in `tac.c`.

It emits pseudo assembly for:

- assignments
- arithmetic operations
- comparisons
- boolean operations
- `print`
- `IFFALSE`
- `GOTO`
- labels

Control flow is preserved using explicit labels and jumps.

## How To Run

Recommended command:

```bash
python3 main.py
```

The driver:

1. builds the compiler
2. runs the parser and semantic analyzer
3. generates TAC
4. applies optimization
5. generates target pseudo assembly

## Expected Outputs

After running, check:

- `quadruples.txt`
- `optimized_quads.txt`
- `target_code.asm`
- `errors.txt`
- `symbol_table.txt`
- `tree_output.txt`
- `trace_output.txt`

## Viva Focus

Be ready to explain:

- what optimization was applied and why it is valid
- how TAC changes before and after optimization
- how arithmetic operations are translated into assembly
- how labels and jumps preserve if/while control flow
- how target code is generated from the intermediate representation and not hardcoded
