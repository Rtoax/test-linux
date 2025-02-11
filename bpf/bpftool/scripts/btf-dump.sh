#!/bin/bash
set -ex

sudo bpftool btf list
# 1 is '1: name [vmlinux]  size 6135770B'
sudo bpftool btf dump id 1
