# Compiler and flags
CC = gcc
CFLAGS = -w

# The final executable name
EXEC = my_compiler

# Default target: build and run
all: build run

# Build the executable
build: $(EXEC)

# Compile everything together
# Note: macOS typically uses -ll to link the lex library
$(EXEC): lex.yy.c y.tab.c symtab.c tac.c
	$(CC) $(CFLAGS) lex.yy.c y.tab.c symtab.c tac.c -o $(EXEC) -ll

# Generate parser C files using bison
# -d creates y.tab.h, -y mimics yacc naming (y.tab.c instead of par.tab.c)
y.tab.c y.tab.h: par.y
	bison -d -y par.y

# Generate lexer C file using flex
lex.yy.c: lex.l y.tab.h
	flex lex.l

# Run the compiled program
run: $(EXEC)
	./$(EXEC)

# Clean up generated files
clean:
	rm -f lex.yy.c y.tab.c y.tab.h $(EXEC)
