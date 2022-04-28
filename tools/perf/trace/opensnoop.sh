#!/bin/bash

# Tracing open
sudo perf trace -e "open*" --syscalls
