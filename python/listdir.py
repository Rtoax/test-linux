#!/bin/env python3
#
# refs:
# https://blog.csdn.net/qq_39839807/article/details/104070761
# https://www.runoob.com/python/os-stat.html
#
import os


hash_ino_file = {}


def file_info(pathname):
    info = os.stat(pathname)
    # print("%s ino %d" % (pathname, info.st_ino))
    hash_ino_file[info.st_ino] = pathname

def recursive_listdir(path):
    files = os.listdir(path)

    for file in files:
        file_path = os.path.join(path, file)

        if os.path.isfile(file_path):
            file_info(file_path)
        elif os.path.isdir(file_path):
            recursive_listdir(file_path)


recursive_listdir('.')
print(hash_ino_file)
