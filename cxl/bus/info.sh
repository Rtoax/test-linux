#!/bin/bash
set -e

if [[ ! -d /sys/bus/cxl/ ]]; then
	exit 0
fi

CMD=ls
[[ $(which find) ]] && CMD=find
[[ $(which tree) ]] && CMD=tree

sudo ${CMD} /sys/bus/cxl/
