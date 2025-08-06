HPC Benchmark
=============

# CUDA Compatiable BLAS

- MetaX Mars X203: Insight C100P Theory
- Nvidia H800

## Theory

| TYPE | X203     | H800     |
| ---- | -------- | -------- |
| INT8 | 450 T    | 3958 T   |
| FP16 | 225 T    | 1979 T   |
| FP32 | 30 T     | 67 T     |
| FP64 | 30 T     | 1 T      |

## API blasGemm()

| TYPE | X203    | H800    |
| ---- | ------- | ------- |
| FP16 | 164 T   | 36.06 T |
| FP32 | 31 T    | 9.15 T  |
| FP64 | 33 T    | 0.19 T  |

## API blasGemmEx()

| TYPE | X203    | H800    |
| ---- | ------- | ------- |
| INT8 | 26 T    | 93 T    |
| FP16 | 163 T   | 492 T   |
| FP32 | 32 T    | 45 T    |
| FP64 | 33 T    | 0.99 T  |

## API blasLtMatmul()

| TYPE | X203    | H800    |
| ---- | ------- | ------- |
| INT8 | 204 T   | N/A     |
| FP16 | 168 T   | 521 T   |
| FP32 | 33 T    | 46 T    |
| FP64 | 33 T    | 0.96 T  |


# Links

- https://www.chaoqing-i.com/upload/20231128/NVIDIA%20H800%20GPU%20Datasheet.pdf
