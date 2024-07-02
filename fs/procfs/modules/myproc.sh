#!/bin/bash

sudo insmod myproc.ko

echo Hello World | sudo tee /proc/myproc
cat /proc/myproc

sudo rmmod myproc
