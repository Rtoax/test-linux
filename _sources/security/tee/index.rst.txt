TEE (Trusted Execution Environment)
===================================

目前可信执行环境的实现技术主要有 `Intel` 的 `SGX`, AMD 的 `SEV`, `ARM` 的 `TrustZone`

.. list-table::
   :header-rows: 1

   * - Tech
     - Protected Bbject
   * - AMD SEV
     - Virtual Machine
   * - Intel SGX
     - Application/Process
   * - ARM TrustZone
     - System


.. toctree::
   :maxdepth: 1

   amd/sev
   arm/trustzone
   intel/sgx


Links
-----

- https://github.com/OP-TEE/optee_os
