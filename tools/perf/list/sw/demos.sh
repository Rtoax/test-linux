#!/bin/bash
perf list sw
sudo perf stat -e page-faults
sudo perf stat -e task-clock,bpf-output
