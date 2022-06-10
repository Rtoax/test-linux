#!/bin/bash

# 显示任意给定的二进制对象 BPF 类型格式(BTF)信息
# BTF使用元数据信息注释程序解耦股，可以用来帮助调试程序
sudo bpftool btf dump id 54
