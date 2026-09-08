#!/bin/bash
# 测试 磁盘写
# 荣涛 2021年12月16日

OUT_DIR=/home/rongtao/

for ((i=1;i<10000000;i++))
do
	echo -e "\033[1;31m=== $i = `date` ===\033[m"
	dd if=/dev/zero of=$OUT_DIR/delete-me bs=4k count=262144
	rm -f $OUT_DIR/delete-me
done
