#!/bin/bash

# Tracing syscalls
sudo perf trace

# Tracing open/openat for 4 events
sudo perf trace -e open* --max-events 4
