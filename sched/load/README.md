LOAD
====

# 概念

PELT: Per-Entity Load Tracking
WALT: Window-Assisted Load Tracking 窗口辅助负载追踪算法
EAS: Energy Aware Scheduling 绿色节能调度

# CPU负载计算方法

`CPU的负载 = 就绪队列的总权重`

同时需要考虑历史负载。

`CPU的负载 = ( 运行时间 / 总时间 ) * 就绪队列的总权重`

# 衰减效应

历史工作负载在时间轴上会有衰减效应。

# PELT - Per-Entiry Load Tracking

引入无穷几何级数累加(the accumulation of an infinite geometric series).
