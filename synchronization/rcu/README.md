RCU - Read Copy Update
======================

# Keywords

- Grace Period (GP) 宽限期 (临界区)
- Quiescent Period (QP) 静默期
- Quiescent Status (QS) 静止状态


# kthread: rcu_sched

## /sys/module/rcutree/parameters/

- `jiffies_till_sched_qs`: 控制**宽限期GP**的检测频率（单位：jiffies）
- `blimit`: 单次处理的最大回调函数数量
- `gp_cleanup_delay`: 宽限期结束后的延迟时间（用于调试）


# debud

- `/sys/kernel/tracing/events/rcu`
- `/sys/kernel/debug/tracing/events/rcu`


# Links

- https://en.wikipedia.org/wiki/Read-copy-update
- https://www.kernel.org/doc/html/latest/RCU/whatisRCU.html
- LWN: [What is RCU, Fundamentally?](https://lwn.net/Articles/262464/)

