#!/bin/bash

# Show USDT list of Bin.
sudo bpftrace -l usdt:/usr/bin/bash:*
