HPC (High Performance Computing)
================================

# Data Types

```
      S1    E15                                F112
FP128|-|-----------|------------------------- ... ---------------------------|

      S1    E11                                F52
FP64 |-|-----------|----------------------------------------------------|

      S1   E8               F23
FP32 |-|--------|-----------------------|

      S1   E8        F10
TF32 |-|--------|----------|

      S1  E5      F10
FP16 |-|-----|----------|

      S1   E8       F7
BF16 |-|--------|-------|

      S1 E4  F3
FP8  |-|----|---| E4M3

      S1 E5   F2
FP8  |-|-----|--| E5M2

          E8
FP8  |----------| E8M0 (CUDA>=13)

     S1 E2  F3
FP6  |-|--|---| E2M3

     S1 E3  F2
FP6  |-|---|--| E3M2

     S1 E2 F1
FP4  |-|--|-| E2M1
```

> S-Sign, E-Exponent(指数), F-Fraction(分数)


# ISA

## ISA compare

- commit bf095f941a58 ("hpc: isa/elf compare: hip, cuda, hpcc")


# Links

- [IEEE 754-2008](https://en.wikipedia.org/wiki/IEEE_754-2008_revision)
- [Single-precision floating-point format](https://en.wikipedia.org/wiki/Single-precision_floating-point_format)
