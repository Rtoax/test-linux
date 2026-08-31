#!/bin/bash
set -e
sysbench memory --memory-block-size=1M --memory-total-size=4G --threads=4 run
