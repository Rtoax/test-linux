Process - 进程 (task_struct)
============================

* `struct task_struct` abstract `process`.
* A module to traverse the tasks list with RCU synchronization.


TSS 任务状态段 task state segment
=================================

不要把它和 任务切换 关联起来（切记），他只是位于内存中的一段数据.
