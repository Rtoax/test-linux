#!/bin/bash

# Show uprobe/uretprobe list of Bin.
sudo bpftrace -l uprobe:/usr/bin/bash:*
