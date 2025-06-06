Process Schedule
================

# Key Words

- **等效让渡时长差值**


# Kernel Threads

- kblockd/%u:
- ksoftirqd/%u: 处理软中断
- migration/%u: 内核线程“迁移”的作用是将线程从高负载的 CPU 移动到不拥挤的 CPU


# Priority

```
                                                  -20 ~ 10 (nice)
+-----------------------------------------+----------------------+
|                  1 ~ 99                 |       100 ~ 139      |  Priority
+-----------------------------------------+----------------------+
                 SCHED_FIFO                 SCHED_NORMAL
                                            (SCHED_OTHER)
                 SCHED_RR                   SCHED_BATCH
                                            SCHED_IDLE

|                       sched_setscheduler(2)                    |
|                       sched_getscheduler(2)                    |

|            sched_setparam(2)            |    setpriority(2)    |
|            sched_getparam(2)            |    getpriority(2)    |
|                                         |    nice(2)           |
|            sched_get_priority_min(2)    |                      |
|            sched_get_priority_max(2)    |                      |
```

> see also 'chrt --max'

|       Policy      |  Priority   |   Nice   |  top PR    |
| ----------------- | ----------- | -------- | ---------- |
| `SCHED_FIFO`      |   0 - 99    |          |  -1 - P    |
| `SCHED_RR`        |   0 - 99    |          |  -1 - P    |
| `SCHED_DEADLINE`  |             |          |            |
| `SCHED_NORMAL`    | 100 - 139   | -20 - 10 | 20 + Nice  |
| `SCHED_BATCH`     | 100 - 139   | -20 - 10 | 20 + Nice  |
| `SCHED_IDLE`      | 100 - 139   | -20 - 10 | 20 + Nice  |


```bash
$ ps -eo state,uid,pid,ppid,pri,rtprio,time,comm
```
