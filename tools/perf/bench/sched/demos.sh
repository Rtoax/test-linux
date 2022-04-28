#!/bin/bash

# executing 1000000 pipe operations between two tasks
# 在两个任务之间执行 1000000 次管道操作
perf bench sched pipe
perf bench --format=simple sched pipe
