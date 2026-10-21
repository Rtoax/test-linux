===========
NVIDIA CUDA
===========

CUDA Debugging
--------------

cuda-gdb
~~~~~~~~

.. code-block:: bash

    $ CUDA_DEVICE_WAITS_ON_EXCEPTION=1 cuda-gdb ./your-program


compute-sanitizer
~~~~~~~~~~~~~~~~~

.. code-block:: bash

    $ compute-sanitizer --tool=memcheck ./your-program


Links
-----

- CUDA Download: https://developer.nvidia.com/cuda-downloads
        - https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2404/sbsa/
- CUDA DNF Repos: https://developer.download.nvidia.cn/compute/cuda/repos/
        - CUDA RHEL 9 x86 RPM: https://developer.download.nvidia.cn/compute/cuda/repos/rhel9/x86_64/
- CUDA opensource 13.0.1: https://developer.download.nvidia.cn/compute/cuda/opensource/13.0.1/
- CUDA C++ Programming Guide: https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html
- CUDA C++ Best Practices Guide: https://docs.nvidia.com/cuda/cuda-c-best-practices-guide/index.html
