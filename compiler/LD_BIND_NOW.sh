#!/bin/bash
# TODO: see man ld.so

LD_BIND_NOW=1
export LD_BIND_NOW

sudo chrt --fifo 1 /usr/bin/ls
