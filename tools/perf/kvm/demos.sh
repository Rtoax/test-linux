#!/bin/bash

sudo perf kvm --host -o perf.data stat record -p $pid
sudo perf kvm -i perf.data stat report

# https://rtoax.blog.csdn.net/article/details/120677586
sudo perf kvm --host --guest record -a -o my.perf.data
sudo perf kvm --host --guest report -i my.perf.data

sudo perf stat -e 'kvm:*' -a sleep 10s
