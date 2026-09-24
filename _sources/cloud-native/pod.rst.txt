===
Pod
===

Namespace
---------

Pod 内的容器都共享哪些内容

.. list-table::
   :header-rows: 1

   * - Type
     - Shared
   * - Network Namespace
     - yes
   * - Volumes
     - yes
   * - IPC Namespace
     - yes
   * - UTS Namespace
     - yes
   * - PID Namespace
     - no (optional)
   * - 资源限制
     - 间接共享
