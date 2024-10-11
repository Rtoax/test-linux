#!/bin/bash
# see ld.so(8) dlopen(3)

LD_BIND_NOW=1
export LD_BIND_NOW

sudo chrt --fifo 1 /usr/bin/ls
