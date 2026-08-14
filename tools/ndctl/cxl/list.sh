#!/bin/bash
set -e

readonly MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[].memdev') )

# Check info, see commit 5a32ccae21a6 ("cxl: cxl.sh: check decoder informations")
sudo cxl list -D
sudo cxl list -D -d decoder0.0
sudo cxl list -M -d decoder0.0
# Bus and dimm
# commit a8b5d8d7094b ("cxl: ndctl list: shows bus and dimm info")
sudo ndctl list -BD

