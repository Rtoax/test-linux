#!/bin/bash

# Running 'futex/hash' benchmark:
# Run summary [PID 61010]: 12 threads, each operating on 1024 [private] futexes for 10 secs.
perf bench futex hash
