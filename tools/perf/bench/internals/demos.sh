#!/bin/bash

# Running 'internals/kallsyms-parse' benchmark:
#  Average kallsyms__parse took: 64.449 ms (+- 0.067 ms)
perf bench internals kallsyms-parse
