
=== TARGET CODE (MIPS PSEUDO-ASSEMBLY) ===
.data
    # Variables mapped dynamically to RAM

.text
MAIN:
    LOAD R1, 7
    STORE R1, t0
    LOAD R1, 2
    LOAD R2, t0
    MUL R3, R1, R2
    STORE R3, t1
    LOAD R1, t1
    STORE R1, a
    LOAD R1, 15
    STORE R1, b
    LOAD R1, 0
    STORE R1, sum

L0:
    LOAD R1, a
    LOAD R2, b
    SLT R3, R1, R2
    STORE R3, t2
    LOAD R1, b
    LOAD R2, 0
    SNE R3, R1, R2
    STORE R3, t3
    LOAD R1, t2
    LOAD R2, t3
    AND R3, R1, R2
    STORE R3, t4
    LOAD R1, t4
    BEQZ R1, L1    # Branch if Zero (False)
    LOAD R1, a
    LOAD R2, 2
    MUL R3, R1, R2
    STORE R3, t5
    LOAD R1, t5
    STORE R1, temp
    LOAD R1, t6
    LOAD R2, 0
    SEQ R3, R1, R2
    STORE R3, t7
    LOAD R1, a
    LOAD R2, 5
    SGT R3, R1, R2
    STORE R3, t8
    LOAD R1, t7
    LOAD R2, t8
    OR R3, R1, R2
    STORE R3, t9
    LOAD R1, t9
    BEQZ R1, L2    # Branch if Zero (False)
    LOAD R1, sum
    LOAD R2, temp
    ADD R3, R1, R2
    STORE R3, t10
    LOAD R1, t10
    STORE R1, sum
    JUMP L3

L2:
    LOAD R1, sum
    LOAD R2, 1
    SUB R3, R1, R2
    STORE R3, t11
    LOAD R1, t11
    STORE R1, sum

L3:
    LOAD R1, a
    LOAD R2, 1
    ADD R3, R1, R2
    STORE R3, t12
    LOAD R1, t12
    STORE R1, a
    JUMP L0

L1:
    LOAD R1, b
    LOAD R2, a
    SUB R3, R1, R2
    STORE R3, t13
    LOAD R1, sum
    LOAD R2, t13
    DIV R3, R1, R2
    STORE R3, t14
    LOAD R1, t14
    STORE R1, avg
    LOAD R1, avg
    LOAD R2, 5.0
    SLT R3, R1, R2
    STORE R3, t15
    LOAD R1, t16
    BEQZ R1, L4    # Branch if Zero (False)
    LOAD R1, sum
    PRINT R1
    JUMP L5

L4:
    LOAD R1, avg
    PRINT R1

L5:
    HALT
==========================================

