# =================================================================
# COMPILER PIPELINE AUTOMATON (PHASE V)
# =================================================================

CC = gcc
BISON = bison
FLEX = lex

# Suppress warnings for a cleaner output during presentation
CFLAGS = -w 

# The default target executed when typing just 'make'
all: run

build:
	$(BISON) -d -y par.y
	$(FLEX) lex.l
	$(CC) $(CFLAGS) lex.yy.c y.tab.c symtab.c tac.c -o my_compiler

run: build
	@echo "=========================================================="
	@echo "🚀 INITIATING MASTER COMPILER PIPELINE (PHASE V)"
	@echo "=========================================================="
	@./my_compiler

clean:
	rm -f lex.yy.c y.tab.c y.tab.h my_compiler
