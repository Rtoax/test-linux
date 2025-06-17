#!/bin/bash
set -e

# create region 0-3
sudo cxl create-region -d decoder0.0 -m mem0 -s 1024M -t ram
sudo cxl create-region -d decoder0.0 -m mem1 -s 1024M -t ram
sudo cxl create-region -d decoder0.0 -m mem2 -s 1024M -t ram
sudo cxl create-region -d decoder0.0 -m mem3 -s 1024M -t ram

sudo cxl enable-region region0
sudo cxl disable-region region0
sudo cxl destroy-region region0
