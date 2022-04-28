#!/bin/bash
perf list hw
sudo perf stat -e cache-misses,bus-cycles,cpu-cycles
