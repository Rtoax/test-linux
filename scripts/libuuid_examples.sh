#!/bin/bash
set -e

. libuuid.sh

for i in `seq 1 10`; do
	echo "$(__gen_uuid_od) (od)"
	echo "$(gen_uuid)"
done
