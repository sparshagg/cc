# Lab 5: Symbol Table and Semantic Analysis

This lab extends the compiler pipeline beyond parsing by adding:

- symbol table management
- scope handling
- memory offset assignment
- semantic validation

It corresponds to the evaluation phase for:

- Question 2: Symbol Table and Scope Handling
- Question 3: Semantic Analysis

## Objective

The parser now works together with a symbol table and semantic checks.

The implementation supports:

- storage of variable name, type, scope, declaration line, initialization status, and memory offset
- insertion and lookup operations
- nested block scopes
- semantic validation for undeclared variables, redeclarations, type mismatches, invalid conditions, and uninitialized uses

## Files

- `main.py`: build-and-run driver for the whole lab
- `par.y`: parser with semantic actions
- `lex.l`: lexer
- `symtab.h`: symbol table interface
- `symtab.c`: symbol table implementation
- `input`: input program
- `errors.txt`: generated compilation error log
- `symbol_table.txt`: generated symbol table snapshot
- `tree_output.txt`: generated AST output
- `trace_output.txt`: generated parser trace
- `ll1_theory_output.txt`: generated FIRST/FOLLOW and LL(1) theory output

## Implementation Summary

### Symbol Table

The symbol table is implemented in `symtab.c` as a hash table of symbol records.

Each record stores:

- variable name
- data type
- scope
- declaration line
- initialization status
- memory offset

The parser inserts declarations into the symbol table and looks up identifiers during assignments, expressions, and print statements.

### Scope Handling

Block entry and exit are handled using `curr_scope` in `par.y`.

- entering `{` increases the scope level
- exiting `}` deletes all symbols from that scope
- lookup prefers the nearest visible scope

### Semantic Checks

This lab reports:

- redeclaration in the same scope
- use of undeclared variables
- use of uninitialized variables
- type mismatch in assignment
- invalid boolean conditions
- invalid modulo on float operands

## How To Run

Recommended command:

```bash
python3 main.py
```

The driver:

1. builds the C compiler using Bison, Lex/Flex, and GCC
2. runs the parser and semantic analyzer
3. generates output files
4. generates LL(1) theory output for FIRST/FOLLOW and stack trace

## Expected Outputs

After running, check:

- `errors.txt`
- `symbol_table.txt`
- `tree_output.txt`
- `trace_output.txt`
- `ll1_theory_output.txt`

## Viva Focus

Be ready to explain:

- symbol table data structure
- insertion and lookup logic
- how nested scopes are handled
- memory offset assignment
- why each semantic error is detected
- how semantic analysis is integrated with the parser
