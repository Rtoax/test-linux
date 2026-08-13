#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao. All rights reserved.

. /etc/os-release

readonly OS=${ID}
readonly OS_VERSION=${VERSION_ID}
readonly OSV="${OS}:${OS_VERSION}"

readonly DISTS_RHEL_LIKE=( fedora centos rhel almalinux openEuler cclinux
			opencloudos kylin tencentos )
readonly DISTS_DEBIAN_LIKE=( debian ubuntu )
readonly DISTS_SUSE_LIKE=( suse opensuse opensuse-leap )
readonly DISTS_ALPINE_LIKE=( alpine )

# $@: operating system names, like: fedora rhel
# echo "YES" if matched
is_os()
{
	local oss=( $@ )
	if [[ " ${oss[@]} " =~ " ${OS} " ]] || \
	   [[ " ${oss[@]} " =~ " ${OSV} " ]]; then
		echo YES
	fi
	return 0
}

is_rhel_like()
{
	is_os ${DISTS_RHEL_LIKE[@]}
	return 0
}

is_debian_like()
{
	is_os ${DISTS_DEBIAN_LIKE[@]}
	return 0
}
