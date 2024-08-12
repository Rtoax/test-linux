Process Schedule
================

# Key Words

- **等效让渡时长差值**


# Kernel Threads

- kblockd/%u:
- ksoftirqd/%u: 处理软中断
- migration/%u: 内核线程“迁移”的作用是将线程从高负载的 CPU 移动到不拥挤的 CPU

# Prio

```
                                  -20 ~ 10 (nice)
+-------------------------------+-------------+
|        0 ~ 99                 | 100 ~ 139   |  Priority
+-------------------------------+-------------+
          SCHED_FIFO              SCHED_NORMAL
          SCHED_RR                SCHED_BATCH
                                  SCHED_IDLE
```

|       Policy      |  Priority   |   Nice   |
| ----------------- | ----------- | -------- |
| `SCHED_FIFO`      | 0 - 99      |          |
| `SCHED_RR`        | 0 - 99      |          |
| `SCHED_DEADLINE`  |             |          |
| `SCHED_NORMAL`    | 100 - 139   | -20 - 10 |
| `SCHED_BATCH`     | 100 - 139   | -20 - 10 |
| `SCHED_IDLE`      | 100 - 139   | -20 - 10 |


```bash
$ ps -eo state,uid,pid,ppid,rtprio,time,comm
```
