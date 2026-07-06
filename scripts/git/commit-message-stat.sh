#!/bin/bash
# Copyright (C) 2026 Rong Tao
set -e

# Statistic os
stat_os() {
	git log --format=%B | grep "Vers:" | sed -E 's/.*Vers: ([^,]*),.*/\1/' | sort | uniq -c
}
stat_os_awk() {
	git log --format=%B | awk '/Vers:/ {split($0, a, ","); sub(/.*Vers: /, "", a[1]); print a[1]}' | sort | uniq -c
}

stat_linux() {
	git log --format=%B | awk -F', ' '/Vers:/ {print $2}' | sort | uniq -c
}

echo "------------- linux ---------------"
stat_linux
echo "------------- os ---------------"
stat_os
