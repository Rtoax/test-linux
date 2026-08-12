#!/bin/bash
set -e

. libuuid.sh

for i in `seq 1 10`; do
	gen_uuid
done
