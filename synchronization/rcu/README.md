RCU - Read Copy Update
======================

- Grace period (GP) 宽限期 (`/sys/module/rcutree/parameters/jiffies_till_sched_qs`)
- Quiescent period (QP) 静默期


# rcu_sched

## /sys/module/rcutree/parameters/

- `jiffies_till_sched_qs`: 控制宽限期的检测频率（单位：jiffies）
- `blimit`: 单次处理的最大回调函数数量
- `gp_cleanup_delay`: 宽限期结束后的延迟时间（用于调试）


# debud

- `/sys/kernel/tracing/events/rcu`
- `/sys/kernel/debug/tracing/events/rcu`


# Links

- https://en.wikipedia.org/wiki/Read-copy-update
- https://www.kernel.org/doc/html/latest/RCU/whatisRCU.html
- LWN: [What is RCU, Fundamentally?](https://lwn.net/Articles/262464/)

