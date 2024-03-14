#!/bin/bash
# Share windows directory to Linux
#
# 1. on windows, 文件夹右键-属性-共享-共享
# 2. "\\R11017001\OpenSource"
# 3. mount -t cifs -o username=rongtao,password=Rong1234 //10.170.6.24/OpenSource /mnt/windows/

USER=rongtao
PASSWD="Rong1234"

SRC_DIR="//10.170.6.24/OpenSource"
DST_DIR="/mnt/windows/"

mount -t cifs -o username=$USER,password=$PASSWD $SRC_DIR $DST_DIR

