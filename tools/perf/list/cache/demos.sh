#!/bin/bash
sudo perf list cache
sudo perf stat -e L1-dcache-load-misses
