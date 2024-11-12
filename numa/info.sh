#!/bin/bash
set -e

sudo dmesg | grep -oe "node[[:space:]]\{1,\}[[:digit:]]\{1,2\}\\: \[mem 0x[0-9a-fA-F]\{16\}-0x[0-9a-fA-F]\{16\}\]"
