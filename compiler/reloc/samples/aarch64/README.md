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
```


# Links

- https://github.com/ARM-software/abi-aa/blob/main/aaelf64/aaelf64.rst
