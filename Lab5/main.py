import sys
import re
import subprocess
import os


def build_and_run_c_compiler():
    print("="*65)
    print("="*65)
    
    print("[*] Compiling C Source Code (Bison -> Lex -> GCC)...")
    try:
        subprocess.run(["bison", "-d", "-y", "par.y"], check=True, stderr=subprocess.DEVNULL)
        subprocess.run(["lex", "lex.l"], check=True, stderr=subprocess.DEVNULL)
        subprocess.run(["gcc", "lex.yy.c", "y.tab.c", "symtab.c", "-o", "my_compiler"], check=True)
    except subprocess.CalledProcessError:
        print("\n[!] FATAL ERROR: C Compilation Failed.")
        sys.exit(1)

    print("[*] Running LALR(1) Parser & Semantic Analyzer...")
    subprocess.run(["./my_compiler"], capture_output=True, text=True)
    
    if os.path.exists("errors.txt"):
        print("  [+] SUCCESS: Error Log             -> 'errors.txt'")
    if os.path.exists("symbol_table.txt"):
        print("  [+] SUCCESS: Semantic Symbol Table -> 'symbol_table.txt'")
    if os.path.exists("tree_output.txt"):
        print("  [+] SUCCESS: Abstract Syntax Tree  -> 'tree_output.txt'")
    if os.path.exists("trace_output.txt"):
        print("  [+] SUCCESS: LALR Internal Trace   -> 'trace_output.txt'")

#ll1
grammar = {
    'PROG': [['SLIST']],
    'SLIST': [['STMT', 'SLIST'], ['eps']],
    'STMT': [['DECL'], ['ASGN'], ['WHL'], ['IF_STMT'], ['PRNT'], ['BLK']],
    'DECL': [['TYP', 'id', ';']],
    'TYP': [['int'], ['float']],
    'ASGN': [['id', '=', 'EXPR', ';']],
    'WHL': [['while', '(', 'EXPR', ')', 'BLK']],
    'IF_STMT': [['if', '(', 'EXPR', ')', 'BLK', 'ELSEPART']],
    'ELSEPART': [['else', 'BLK'], ['eps']],
    'PRNT': [['print', '(', 'id', ')', ';']],
    'BLK': [['{', 'SLIST', '}']],
    'EXPR': [['TERM', 'EXPR_PRIME']],
    'EXPR_PRIME': [
        ['+', 'TERM', 'EXPR_PRIME'], ['-', 'TERM', 'EXPR_PRIME'], 
        ['<', 'TERM', 'EXPR_PRIME'], ['>', 'TERM', 'EXPR_PRIME'],
        ['<=', 'TERM', 'EXPR_PRIME'], ['>=', 'TERM', 'EXPR_PRIME'],
        ['==', 'TERM', 'EXPR_PRIME'], ['!=', 'TERM', 'EXPR_PRIME'],
        ['&&', 'TERM', 'EXPR_PRIME'], ['||', 'TERM', 'EXPR_PRIME'], ['eps']
    ],
    'TERM': [['FACTOR', 'TERM_PRIME']],
    'TERM_PRIME': [
        ['*', 'FACTOR', 'TERM_PRIME'], ['/', 'FACTOR', 'TERM_PRIME'], 
        ['%', 'FACTOR', 'TERM_PRIME'], ['eps']
    ],
    'FACTOR': [['(', 'EXPR', ')'], ['id'], ['num'], ['!', 'FACTOR']]
}

terminals = {
    'id', 'num', 'int', 'float', ';', '=', 'while', '(', ')', 'if', 'else', 
    'print', '{', '}', '+', '-', '*', '/', '%', '<', '>', '<=', '>=', 
    '==', '!=', '&&', '||', '!', 'eps', '$'
}
non_terminals = list(grammar.keys())
first = {nt: set() for nt in non_terminals}
follow = {nt: set() for nt in non_terminals}
parse_table = {nt: {} for nt in non_terminals}

def tokenize(code):
    tokens = []
    specs = [
        ('num', r'\d+(\.\d+)?'),
        ('id', r'[a-zA-Z_]\w*'),
        ('op', r'==|!=|<=|>=|&&|\|\||<|>|\+|-|\*|/|%|!|='),
        ('punc', r'[;(){}]'),
        ('skip', r'[ \t\n]+')
    ]
    keywords = {'int', 'float', 'if', 'else', 'while', 'print'}
    tok_regex = '|'.join('(?P<%s>%s)' % pair for pair in specs)
    
    for mo in re.finditer(tok_regex, code):
        kind = mo.lastgroup
        val = mo.group()
        if kind == 'skip': continue
        elif kind == 'id': tokens.append(val if val in keywords else 'id')
        elif kind in ['op', 'punc']: tokens.append(val)
        elif kind == 'num': tokens.append('num')
    tokens.append('$')
    return tokens

# first follow and stack trace
def compute_first():
    changed = True
    while changed:
        changed = False
        for nt, prods in grammar.items():
            for prod in prods:
                symbol = prod[0]
                if symbol in terminals:
                    if symbol not in first[nt]:
                        first[nt].add(symbol)
                        changed = True
                else: 
                    for f in first[symbol]:
                        if f not in first[nt]:
                            first[nt].add(f)
                            changed = True

def compute_follow():
    follow['PROG'].add('$')
    changed = True
    while changed:
        changed = False
        for nt, prods in grammar.items():
            for prod in prods:
                for i in range(len(prod)):
                    symbol = prod[i]
                    if symbol in non_terminals:
                        if i + 1 < len(prod):
                            next_sym = prod[i+1]
                            if next_sym in terminals:
                                if next_sym not in follow[symbol]:
                                    follow[symbol].add(next_sym)
                                    changed = True
                            else:
                                for f in first[next_sym] - {'eps'}:
                                    if f not in follow[symbol]:
                                        follow[symbol].add(f)
                                        changed = True
                        if i == len(prod) - 1 or (i + 1 < len(prod) and 'eps' in first.get(prod[i+1], [])):
                            for f in follow[nt]:
                                if f not in follow[symbol]:
                                    follow[symbol].add(f)
                                    changed = True

def build_table():
    for nt, prods in grammar.items():
        for prod in prods:
            first_of_prod = set()
            if prod[0] in terminals:
                first_of_prod.add(prod[0])
            else:
                first_of_prod.update(first[prod[0]])
            
            for term in first_of_prod - {'eps'}:
                parse_table[nt][term] = prod
            
            if 'eps' in first_of_prod:
                for term in follow[nt]:
                    parse_table[nt][term] = prod

def parse_ll1(code_string):
    tokens = tokenize(code_string)
    stack = ['$', 'PROG']
    ptr = 0
    
    print("\n" + "="*80)
    print("3. LL(1) PARSING STACK TRACE")
    print("="*80)
    print(f"{'STACK':<35} | {'INPUT STREAM':<30} | {'ACTION'}")
    print("-" * 80)

    while stack[-1] != '$':
        top = stack[-1]
        tok = tokens[ptr]
        
        stack_str = " ".join(stack[-8:]) 
        if len(stack) > 8: stack_str = "... " + stack_str
        input_str = " ".join(tokens[ptr:ptr+6]) 
        if ptr+6 < len(tokens): input_str += " ..."

        if top == tok:
            print(f"{stack_str:<35} | {input_str:<30} | MATCH '{tok}'")
            stack.pop()
            ptr += 1
        elif top in terminals:
            print(f"\n[!] SYNTAX ERROR: Expected '{top}', found '{tok}'")
            return
        elif tok in parse_table[top]:
            rule = parse_table[top][tok]
            print(f"{stack_str:<35} | {input_str:<30} | RULE: {top} -> {' '.join(rule)}")
            stack.pop()
            if rule != ['eps']:
                for sym in reversed(rule):
                    stack.append(sym)
        else:
            print(f"\n[!] SYNTAX ERROR: No rule in table for [{top}, {tok}]")
            return

    print(f"{'$':<35} | {'$':<30} | ACCEPTED SUCCESSFULLY")


def generate_ll1_file(test_code):
    print("[*]  LL(1) Theory Engine Data...")
    
    compute_first()
    compute_follow()
    build_table()
    
    # write to text files
    original_stdout = sys.stdout
    with open('ll1_theory_output.txt', 'w') as f:
        sys.stdout = f  # Redirect
        
        print("="*40 + "\n1. COMPUTED FIRST SETS\n" + "="*40)
        for nt in non_terminals: print(f"FIRST({nt:10}) = {first[nt]}")
        
        print("\n" + "="*40 + "\n2. COMPUTED FOLLOW SETS\n" + "="*40)
        for nt in non_terminals: print(f"FOLLOW({nt:9}) = {follow[nt]}")
        
        parse_ll1(test_code)
        
    sys.stdout = original_stdout # Restore normal printing
    print("  [+] SUCCESS: Theory Output generated -> 'll1_theory_output.txt'")

if __name__ == "__main__":
    
    build_and_run_c_compiler()
    
    
    try:
        with open('input', 'r') as file:
            test_code = file.read()
    except FileNotFoundError:
        print("\n[!] ERROR: Could not find the 'input' file.")
        sys.exit(1)
        
  
    generate_ll1_file(test_code)
    
    print("="*65)
    print("="*65)