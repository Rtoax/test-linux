#!/bin/bash
pid=$(pidof stress)
cat /proc/${pid}/status | grep ^Vm
