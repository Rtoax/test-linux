=========
Scheduler
=========

:doc:`abbrev`


Key Words
---------

- **等效让渡时长差值**


Contents
--------

.. toctree::
   :maxdepth: 1

   cfs
   deadline
   eevdf
   load
   migration
   pelt
   preempt
   rt
   rtlinux
   rtos
   smt
   task_struct
   ttwu


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
   * - :doc:`cfs`
     - 抢占式
     - Linux默认调度器，基于虚拟运⾏时间（vruntime）分配CPU，红⿊树管理任务队列
     - 低延迟、⾼公平性
     - 对实时任务⽀持需额外配置
     - 通⽤系统（现代Linux内核）



Priority
--------

.. code-block:: text

                                                    -20 ~ 10 (nice)
  +-----------------------------------------+----------------------+
  |                  1 ~ 99                 |       100 ~ 139      |  Priority
  +-----------------------------------------+----------------------+
  |                SCHED_FIFO               | SCHED_NORMAL (SCHED_OTHER)
  |                SCHED_RR                 | SCHED_BATCH          |
  |                                         | SCHED_IDLE           |
  
  |                       sched_setattr(2)                         |
  |                       sched_getattr(2)                         |
  |                       sched_setscheduler(2)                    |
  |                       sched_getscheduler(2)                    |
  
  |            sched_setparam(2)            |    setpriority(2)    |
  |            sched_getparam(2)            |    getpriority(2)    |
  |                                         |    nice(2)           |
  |            sched_get_priority_min(2)    |                      |
  |            sched_get_priority_max(2)    |                      |


see also 'chrt --max'.

.. code-block:: text

  |     Policy      |  Priority   |   Nice   |  top PR    |
  | --------------- | ----------- | -------- | ---------- |
  | SCHED_FIFO      |   0 - 99    |          |  -1 - P    |
  | SCHED_RR        |   0 - 99    |          |  -1 - P    |
  | SCHED_DEADLINE  |             |          |            |
  | SCHED_NORMAL    | 100 - 139   | -20 - 10 | 20 + Nice  |
  | SCHED_BATCH     | 100 - 139   | -20 - 10 | 20 + Nice  |
  | SCHED_IDLE      | 100 - 139   | -20 - 10 | 20 + Nice  |
