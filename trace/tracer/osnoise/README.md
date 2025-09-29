OSNOISE - Operating System Noise
================================


- 开启

```
# cd /sys/kernel/tracing/
# echo osnoise > current_tracer
```

- 查看

```
# cat /sys/kernel/tracing/trace
# tracer: osnoise
#
#                       _-----=> irqs-off
#                      / _----=> need-resched
#                     | / _---=> hardirq/softirq
#                     || / _--=> preempt-depth
#                     ||| / _-=> migrate-disable                         MAX
#                     |||| /     delay                                   SINGLE      Interference counters:
#                     |||||               RUNTIME      NOISE  %% OF CPU  NOISE    +-----------------------------+
#  TASK-PID      CPU# |||||   TIMESTAMP    IN US       IN US  AVAILABLE  IN US     HW    NMI    IRQ   SIRQ THREAD
#     | |         |   |||||      |           |             |    |            |      |      |      |      |      |
  <...>-7267    [000] .......  2001.256521: 1000000        986  99.90140      87      9      0   1032    174      6
  <...>-7268    [001] .......  2001.256536: 1000000       1055  99.89450     689      9      0   1003    197     46
  <...>-7269    [002] .......  2001.256549: 1000000       1596  99.84040    1193      9      0   1001    153     13
  <...>-7270    [003] .......  2001.256564: 1000000        414  99.95860      66      9      0   1000    179      3
  <...>-7271    [004] .......  2001.256575: 1000000       2594  99.74060    1274     17      0   1013    208     46
  <...>-7272    [005] .......  2001.256590: 1000000       4328  99.56720    1131     11      0   1015    208     83
```


- 关闭

```
# echo nop > current_tracer
```


# Links

- https://docs.kernel.org/trace/osnoise-tracer.html

