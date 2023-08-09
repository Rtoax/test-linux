#!/bin/bash 
# 

# 将创建文件 ./initrd.img
sudo dracut ./initrd.img $(uname -r)
