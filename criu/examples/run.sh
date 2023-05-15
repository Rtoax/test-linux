#!/bin/bash

# 编译
gcc test.c -o a.out

# 转储进程到文件，目录
test ! -e imgdir && mkdir imgdir
sudo criu dump -D imgdir/ -j -t $(pidof a.out)

# 恢复进程
sudo criu restore --restore-detached -D imgdir/ -j
test -e imgdir && rm -rf imgdir

