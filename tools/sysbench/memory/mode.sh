#!/bin/bash
set -e
sysbench memory --memory-block-size=1M --memory-total-size=1G --memory-access-mode=rnd run
