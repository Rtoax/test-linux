=========
Scheduler
=========

Scheduler
----------

.. list-table::
   :header-rows: 1

   * - 调度算法
     - 类型
     - 特点
     - 优点
     - 缺点
     - 使用场景
   * - 完全公平调度 (CFS)
     - 抢占式
     - Linux默认调度器，基于虚拟运⾏时间（vruntime）分配CPU，红⿊树管理任务队列
     - 低延迟、⾼公平性
     - 对实时任务⽀持需额外配置
     - 通⽤系统（现代Linux内核）
