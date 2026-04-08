# Lab 4: Parser Implementation

This lab implements two parsing techniques for the same core language:

- Shift-reduce parsing using Flex and Bison
- LL(1) predictive parsing in Python

This is the parser-construction phase of the compiler assignment.

## Objective

The goal of this lab is to move from CFG-based syntactic validation to actual parser implementation.

This lab demonstrates:

- parsing the prescribed evaluation program
- shift-reduce parser trace
- FIRST and FOLLOW computation
- LL(1) predictive parsing
- parsing stack trace

## Files

- `lex.l`: Flex lexer used by the shift-reduce parser
- `par.y`: Bison grammar for shift-reduce parsing
- `ll1.py`: LL(1) parser implementation
- `input`: Evaluation program used as parser input
- `trace_output.txt`: Sample shift-reduce trace output
- `tree_output.txt`: Sample parse tree, LMD, and RMD output

## Shift-Reduce Parser

The Bison parser in `par.y` works as a bottom-up parser.

It:

- reads tokens from the lexer
- performs shift and reduce actions using parser states
- prints a parse trace
- prints the parse tree, LMD, and RMD on success

### How To Run

```bash
bison -d -t par.y
flex lex.l
gcc par.tab.c lex.yy.c -o parser
./parser
```

Note:

- `-t` is required with `bison` because `yydebug = 1` is enabled in `par.y`
- this lab reads from `input`, not `input.txt`

## LL(1) Parser

The Python script `ll1.py` implements an LL(1) predictive parser.

It:

- defines an LL(1)-friendly grammar
- tokenizes the input program
- computes FIRST sets
- computes FOLLOW sets
- builds the predictive parse table internally
- shows the parsing stack trace

### How To Run

```bash
python3 ll1.py
```

## What Changed From Lab 3

Compared to Lab 3, this lab shifts focus away from semantic analysis and toward parser algorithms.

Major changes:

- adds shift-reduce parsing trace
- adds LL(1) parsing
- adds FIRST and FOLLOW computation
- adds stack-based predictive parsing
- keeps syntax parsing but removes most semantic-analysis logic

## Viva Focus

Be ready to explain:

- difference between LL(1) and shift-reduce parsing
- how FIRST and FOLLOW are computed
- how the LL(1) parser selects rules
- what shift and reduce actions mean
- end-to-end flow from token stream to acceptance
