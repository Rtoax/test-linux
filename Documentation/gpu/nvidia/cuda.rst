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


- https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2404/sbsa/
