#!/bin/bash
pid=$(pidof stress)
cat /proc/${pid}/status | grep ^Vm
pidstat  -r --human -p ${pid}
