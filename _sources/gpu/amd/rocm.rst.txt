============
AMD GPU ROCm
============

ROCm - Radeon Open Compute
--------------------------

ROCm is an open-source software platform optimized to extract HPC and AI
workload performance from AMD Instinct GPUs and AMD Radeon GPUs while
maintaining compatibility with industry software frameworks.


ROCm Installation
~~~~~~~~~~~~~~~~~

Debian
^^^^^^

Debian 13
"""""""""

.. code-block:: bash

        $ sudo apt install -y gnupg curl wget software-properties-common
        $ curl -fsSL https://repo.radeon.com/rocm/rocm.gpg.key | \
                sudo tee /etc/apt/trusted.gpg.d/rocm.gpg
        $ echo "deb [arch=amd64] https://repo.radeon.com/rocm/apt/7.0 noble main" | \
                sudo tee /etc/apt/sources.list.d/rocm.list
        $ sudo apt update
        $ sudo apt install -y rocm-libs rocm-llvm


Links
-----

- `AMD ROCm documentation <https://rocm.docs.amd.com/en/latest/>`_
- `ROCm Releases Packages <https://repo.radeon.com/rocm/>`_
- `GitHub AMD ROCm Software <https://github.com/ROCm/ROCm>`_
- `GitHub ROCm systems <https://github.com/ROCm/rocm-systems>`_
- `GitHub ROCm libraries <https://github.com/ROCm/rocm-libraries>`_
- `GitHub hip (retired) <https://github.com/ROCm/hip>`_
- `Accelerator and GPU hardware specifications <https://rocm.docs.amd.com/en/latest/reference/gpu-arch-specs.html>`_
