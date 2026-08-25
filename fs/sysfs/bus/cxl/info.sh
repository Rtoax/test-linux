#!/bin/bash
set -e

if [[ ! -d /sys/bus/cxl/ ]]; then
	exit 0
fi

CMD=ls
[[ $(which find) ]] && CMD=find
[[ $(which tree) ]] && CMD=tree

# commit 371e334caa6f ("cxl: bus: list /sys/bus/cxl/")
sudo ${CMD} /sys/bus/cxl/
