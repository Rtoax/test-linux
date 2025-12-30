#!/bin/bash
sudo perf trace -e sched:sched_wakeup
sudo perf stat -e sched:sched_wakeup
