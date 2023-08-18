#!/bin/bash 

PGID=1

## 查看所有子进程
ps --forest -o pid,tty,stat,time,cmd -g $PGID

## 把所有进程pid放到文本中
PIDS=$(ps --forest -o pid -h -g $PGID)
echo $PIDS

## 按照Pss计算所有进程使用的总内存
for pid in $PIDS; do cat /proc/$pid/smaps; done | awk '/Pss/ {mem += $2} END {print mem, "kB"}'
