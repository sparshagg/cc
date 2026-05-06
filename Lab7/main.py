import sys
import subprocess

# =================================================================
# 1. THE BUILD SYSTEM & C-COMPILER TRIGGER 
# =================================================================
def build_and_run_c_compiler():
    print("="*80, flush=True)
    print("🚀 INITIATING MASTER COMPILER PIPELINE (PHASE V)", flush=True)
    print("="*80, flush=True)
    
    print("\n[*] Step 1: Compiling C Source Code (Bison -> Flex -> GCC)...", flush=True)
    try:
        subprocess.run(["bison", "-d", "-y", "par.y"], check=True, stderr=subprocess.DEVNULL)
        subprocess.run(["flex", "lex.l"], check=True, stderr=subprocess.DEVNULL)
        subprocess.run(["gcc", "lex.yy.c", "y.tab.c", "symtab.c", "tac.c", "-o", "my_compiler"], check=True)
        print("  [+] SUCCESS: C Source Code Compiled Successfully.", flush=True)
    except subprocess.CalledProcessError:
        print("\n[!] FATAL ERROR: C Compilation Failed.", flush=True)
        sys.exit(1)

    print("\n[*] Step 2: Running LALR(1) Compiler Pipeline...\n", flush=True)
    print("="*80, flush=True)
    
    # Executing the compiled binary directly to the console
    subprocess.run(["./my_compiler"])
    
    print("\n" + "="*80, flush=True)
    print("✨ PIPELINE COMPLETE! All outputs have been successfully rendered.", flush=True)
    print("="*80, flush=True)

if __name__ == "__main__":
    build_and_run_c_compiler()
