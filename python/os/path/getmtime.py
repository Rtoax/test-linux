#!/bin/env python
# Get process start time
import os
import time
from datetime import datetime


def get_file_time(file):
    ctime = os.path.getctime(file)
    mtime = os.path.getmtime(file)
    atime = os.path.getatime(file)

    ctime_str = datetime.fromtimestamp(int(ctime))
    mtime_str = datetime.fromtimestamp(int(mtime))
    atime_str = datetime.fromtimestamp(int(atime))

    print("ctime %s, %d" % (ctime_str, ctime))
    print("mtime %s, %d" % (mtime_str, mtime))
    print("atime %s, %d" % (atime_str, atime))

if __name__ == "__main__":
    file = "test.dat"

    fd = os.open(file, os.O_CREAT | os.O_RDWR, 0o644)
    os.close(fd)

    get_file_time(file)

    time.sleep(1)

    get_file_time(file)

    time.sleep(1)

    # this will change mtime
    fd = os.open(file, os.O_CREAT | os.O_RDWR, 0o644)
    os.lseek(fd, 0, os.SEEK_SET)
    os.ftruncate(fd, 0)
    os.write(fd, str(os.getpid()).encode('utf-8'))
    os.close(fd)

    get_file_time(file)
