#!/bin/bash

# 加载程序到内核
sudo bpftool prog load bpf_prog.o /sys/fs/bpf/bpf_prog
