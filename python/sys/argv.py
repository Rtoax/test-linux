#!/bin/env python
import sys

if len(sys.argv) < 2:
    print("Error: No argument provided.")
    sys.exit(1)

for i, a in enumerate(sys.argv[1:]):
    print("argv[%d] %s" % (i, a))
