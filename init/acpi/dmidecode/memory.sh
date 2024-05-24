#!/bin/bash

# 查看内存信息
sudo dmidecode -t memory
sudo dmidecode | grep -A16 "Memory Device$"

# 现有内存数量和内存大小
sudo dmidecode | grep -A16 "Memory Device" | grep "Size" | sed 's/^[ \t]*//'

# 最大支持内存容量
sudo dmidecode | grep "Maximum Capacity" | sed  "s/^[ \t]*//"
