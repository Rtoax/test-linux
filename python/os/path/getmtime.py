#!/bin/env python
# Get process start time
import os
from datetime import datetime


if __name__ == "__main__":
    file = "/etc/os-release"

    ctime = os.path.getctime(file)
    mtime = os.path.getmtime(file)
    atime = os.path.getatime(file)

    ctime_str = datetime.fromtimestamp(int(ctime))
    mtime_str = datetime.fromtimestamp(int(mtime))
    atime_str = datetime.fromtimestamp(int(atime))

    print("ctime %s" % ctime_str)
    print("mtime %s" % mtime_str)
    print("atime %s" % atime_str)
