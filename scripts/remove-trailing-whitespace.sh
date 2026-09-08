#!/bin/bash
# Remove all trailing whitespace from files.
set -e

grep -rIl \
	--exclude-dir=.git \
	--exclude='*.png' \
	--exclude='*.jpg' \
	--exclude='*.pdf' \
	--exclude='*.webp' \
	--exclude='*.avif' . | \
	xargs sed -i 's/[ \t]*$//'
