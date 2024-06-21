#!/bin/bash
set -e

darch=${DARCH}

if [[ -z ${darch} ]]; then
	echo -e "\033[1;31mWARNING: DARCH=arm64 $0\033[m"
fi

# Install depends
./scripts/install-deps.sh --noup --nobase --container

podman pull ${darch:+--arch ${darch}} fedora:40
podman run --rm -ti --volume $PWD:/root/tst-linux ${darch:+--arch ${darch}} fedora:40 bash
