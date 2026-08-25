#!/bin/bash
set -e

. libnbd.sh

echo "All: $(all_dev_ndb)"
echo "Find an idle: $(nbd_find_idle_dev)"
