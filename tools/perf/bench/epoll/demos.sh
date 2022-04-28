#!/bin/bash

# Running 'epoll/wait' benchmark:
# Run summary [PID 60605]: 11 threads monitoring on 64 file-descriptors for 8 secs.
perf bench epoll wait

# Run summary [PID 60765]: 12 threads doing epoll_ctl ops 64 file-descriptors for 8 secs.
perf bench epoll ctl
