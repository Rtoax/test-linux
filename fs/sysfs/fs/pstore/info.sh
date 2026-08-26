#!/bin/bash
set -e

mount | grep pstore || {
	echo "Not found pstore mountpoint"
	exit 0
}
