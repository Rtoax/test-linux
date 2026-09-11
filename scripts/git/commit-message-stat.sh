#!/bin/bash
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Usage: commit-message-stat.sh [downer-commit] [upper-commit]
set -e

from_commit=$1
to_commit=$2
COMMITS_ARG=

if [[ ${from_commit} ]] && [[ ${to_commit} ]]; then
	COMMITS_ARG=${from_commit}..${to_commit}
elif [[ ${from_commit} ]]; then
	echo >&2 "ERROR: need two commits at least"
	exit 1
fi

# Statistic os
stat_os() {
	git log ${COMMITS_ARG} --format=%B | \
	awk -F', ' '
	BEGIN {
		names["almalinux"] = 1
		names["alpine"] = 1
		names["cclinux"] = 1
		names["centos"] = 1
		names["debian"] = 1
		names["fedora"] = 1
		names["kylin"] = 1
		names["opencloudos"] = 1
		names["openeuler"] = 1
		names["opensuse"] = 1
		names["tencentos"] = 1
		names["ubuntu"] = 1
	}
	/^OS:/ {
		sub(/^OS: /, "", $0)
		print $0
	}
	/^Vers(ions)?:/ {
		sub(/.*Vers(ions)?: /, "", $1)
		distro = $1
		sub(/[^A-Za-z].*$/, "", distro)
		if (tolower(distro) in names) {
			print $1
		}
	}' | grep -vE "Vers(ions)?:" | sort | uniq -c
}

stat_linux() {
	git log ${COMMITS_ARG} --format=%B | \
	awk -F', ' '
	/^Vers: / {
		if ($1 ~ /Linux /) {
			sub(/^Vers: /, "", $1)
			# OS Distro maybe contains 'Linux'
			if ($1 ~ /^Linux /) {
				print $1
			}
		}
		if ($2 ~ /Linux /) {
			print $2
		}
	}
	/^Linux: / {
		sub(/Linux: /, "", $1)
		# Avoid "Linux: commit xxxx" lines
		if ($1 ~ "^[0-9]+\\.[0-9]+\\.[0-9]+") {
			print "Linux "$1
		}
	}
	' | sort | uniq -c
}

stat_arch() {
	git log ${COMMITS_ARG} --format=%B | \
		grep "Envs:" | grep -oP 'Arch \K\S+' | sed 's/,$//' | sort | uniq -c
}

echo "------------- linux ---------------"
stat_linux
echo "------------- os ---------------"
stat_os
echo "------------- arch ---------------"
stat_arch
