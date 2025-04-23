aarch64 Relocation
==================

# ELF64 aarch64

```
Name				Value		Calculation	Comment
-------------------------------------------------------------------------------
R_AARCH64_ABS64			257		S + A		No overflow check
R_AARCH64_ABS32			258		S + A
R_AARCH64_ABS16			259		S + A
R_AARCH64_PREL64		260		S + A - P	PC-relative 64-bits, No overflow check
R_AARCH64_PREL32		261		S + A - P	PC-relative 32-bits
R_AARCH64_PREL16		262		S + A - P	PC-relative 16-bits
R_AARCH64_ADR_PREL_PG_HI21	275
R_AARCH64_ADR_PREL_PG_HI21_NC	276
R_AARCH64_ADD_ABS_LO12_NC	277
R_AARCH64_JUMP26		282		S + A - P	Set a B immediate field to bits [27:2] of X; check that -2^27 <= X < 2^27
R_AARCH64_CALL26		283		S + A - P	Set a CALL immediate field to bits [27:2] of X; check that -2^27 <= X < 2^27
R_AARCH64_PLT32			314		S + A - P
```


# Links

- https://github.com/ARM-software/abi-aa/blob/main/aaelf64/aaelf64.rst
