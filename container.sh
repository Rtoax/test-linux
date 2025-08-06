#!/bin/bash
# Copyright (c) 2024-2025 Rong Tao
set -e

IMG=fedora:42

darch=${DARCH}

if [[ -z ${darch} ]]; then
	echo -e "\033[1;31mWARNING: DARCH=arm64 $0\033[m"
fi

# Install depends
./scripts/install-deps.sh --noup --nobase --container

podman pull ${darch:+--arch ${darch}} ${IMG}
podman run --rm -ti --volume $PWD:/root/tst-linux ${darch:+--arch ${darch}} ${IMG} bash
