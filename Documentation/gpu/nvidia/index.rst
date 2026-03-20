==========
NVIDIA GPU
==========

Architecture and Compute Capability
-----------------------------------

.. list-table::
   :widths: 15 15 15
   :header-rows: 1

   * - Architecture
     - Major.Minor
     - nvcc -arch
   * - Blackwell
     - 12.
     - sm_120+
   * - Blackwell
     - 10.
     - sm_100+
   * - Hopper
     - 9.
     - sm_100+
   * - Ada Lovelace
     - 8.9
     - sm_89+
   * - Ampere
     - 8.
     - sm_80+
   * - Turing
     - 7.5
     - sm_75+
   * - Volta
     - 7.0
     - sm_70+
   * - Pascal
     - 6.0
     - sm_60+
   * - Maxwell
     - 5.
     - sm_50+


Precisions
----------

.. list-table::
   :widths: 15 15 15
   :header-rows: 1

   * - Type
     - Blackwell
     - Hopper
   * - Supported Tensor Core precisions
     - FP64, TF32, BF16, FP16, FP8, INT8, FP6, FP4
     - FP64, TF32, BF16, FP16, FP8, INT8
   * - Supported CUDA® Core precisions
     - FP64, FP32, FP16, BF16
     - FP64, FP32, FP16, BF16, INT8

see `NVIDIA Tensor Cores <https://www.nvidia.com/en-us/data-center/tensor-cores/>`_.


Links
-----

- `Nvidia GitHub <https://github.com/NVIDIA>`_
- `CUDA C++ Programming Guide <https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html>`_
- `CUDA C++ Best Practices Guide <https://docs.nvidia.com/cuda/cuda-c-best-practices-guide/index.html>`_

OPS
~~~

- https://www.chaoqing-i.com/upload/20231128/NVIDIA%20H800%20GPU%20Datasheet.pdf

Instruction Set
~~~~~~~~~~~~~~~

- `Turing Instruction Set <https://docs.nvidia.com/cuda/cuda-binary-utilities/index.html#turing-instruction-set>`_
- `NVIDIA Ampere GPU and Ada Instruction Set <https://docs.nvidia.com/cuda/cuda-binary-utilities/index.html#nvidia-ampere-gpu-and-ada-instruction-set>`_
- `Hopper Instruction Set <https://docs.nvidia.com/cuda/cuda-binary-utilities/index.html#hopper-instruction-set>`_
    - https://www.nvidia.com/en-us/data-center/technologies/hopper-architecture/
- `Blackwell Instruction Set <https://docs.nvidia.com/cuda/cuda-binary-utilities/index.html#blackwell-instruction-set>`_
    - https://www.nvidia.com/en-us/data-center/technologies/blackwell-architecture/

Tensor
~~~~~~

- `NVIDIA Tensor Cores <https://www.nvidia.com/en-us/data-center/tensor-cores/>`_

DGX Spark
~~~~~~~~~

- https://github.com/NVIDIA/dgx-spark-playbooks
