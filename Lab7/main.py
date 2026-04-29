import sys
import subprocess

# =================================================================
# 1. THE BUILD SYSTEM & C-COMPILER TRIGGER 
# =================================================================
def build_and_run_c_compiler():
    print("="*80)
    print("🚀 INITIATING MASTER COMPILER PIPELINE (PHASE V)")
    print("="*80)
    
    print("\n[*] Step 1: Compiling C Source Code (Bison -> Lex -> GCC)...")
    try:
        subprocess.run(["bison", "-d", "-y", "par.y"], check=True, stderr=subprocess.DEVNULL)
        subprocess.run(["lex", "lex.l"], check=True, stderr=subprocess.DEVNULL)
        subprocess.run(["gcc", "lex.yy.c", "y.tab.c", "symtab.c", "tac.c", "-o", "my_compiler"], check=True)
        print("  [+] SUCCESS: C Source Code Compiled Successfully.")
    except subprocess.CalledProcessError:
        print("\n[!] FATAL ERROR: C Compilation Failed.")
        sys.exit(1)

    print("\n[*] Step 2: Running LALR(1) Compiler Pipeline...\n")
    print("="*80)
    
    # Executing the compiled binary directly to the console
    subprocess.run(["./my_compiler"])
    
    print("\n" + "="*80)
    print("✨ PIPELINE COMPLETE! All outputs have been successfully rendered.")
    print("="*80)

if __name__ == "__main__":
    build_and_run_c_compiler()