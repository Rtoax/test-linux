#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao

readonly LIBCPU_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))

. ${LIBCPU_ROOT}/liblog.sh

cpu_is_hygon() {
	lscpu | grep -ow HygonGenuine
}
