#!/bin/bash
make clean
make CROSS_COMPILE=aarch64-linux-gnu- STATIC=1
