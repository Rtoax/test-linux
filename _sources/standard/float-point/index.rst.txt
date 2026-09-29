.. SPDX-License-Identifier: GPL-2.0

===========
Float Point
===========

Floating-Point Data Types
-------------------------

- S-Sign(符号)
- E-Exponent(指数)
- F-Fraction(分数)


.. code-block:: text
   :caption: 浮点数格式对比

          S1    E15                                F112
    FP128|-|-----------|------------------------- ... ---------------------------|

          S1    E15                              F63
    FP80 |-|-----------|------------------------ ... ---------------------------|

          S1    E11                                F52
    FP64 |-|-----------|----------------------------------------------------|

          S1   E8               F23
    FP32 |-|--------|-----------------------|

          S1   E8        F10
    TF32 |-|--------|----------| (Tensor Core)

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


Links
-----

- `IEEE 754-2008 standard for floating-point arithmetic <https://en.wikipedia.org/wiki/IEEE_754-2008_revision>`_
- `Single-precision floating-point format <https://en.wikipedia.org/wiki/Single-precision_floating-point_format>`_
- `CUDA Math API Reference Manual <https://docs.nvidia.com/cuda/cuda-math-api/index.html>`_
