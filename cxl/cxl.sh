#!/bin/bash
set -e

# create region 0-3
sudo cxl create-region -d decoder0.0 -s 1024M -t ram -m mem0
sudo cxl create-region -d decoder0.0 -s 1024M -t ram -m mem1
sudo cxl create-region -d decoder0.0 -s 1024M -t ram -m mem2
sudo cxl create-region -d decoder0.0 -s 1024M -t ram -m mem3

# create region0
sudo cxl create-region -d decoder0.0 -s 4096M -t ram -m mem0 mem1 mem2 mem3

sudo cxl enable-region region0
sudo cxl disable-region region0
sudo cxl destroy-region region0
