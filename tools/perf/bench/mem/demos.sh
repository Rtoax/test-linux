#!/bin/bash

# Running 'mem/memset' benchmark:
# function 'default' (Default memset() provided by glibc)
# Copying 1MB bytes ...
perf bench mem memset

#
perf bench mem all
