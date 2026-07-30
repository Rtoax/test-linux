#!/bin/env python
import os

pid = os.fork()
if pid == 0:
    os._exit(0)
os.waitpid(pid, 0)
