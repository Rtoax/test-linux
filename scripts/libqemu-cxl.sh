#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao. All rights reserved.

readonly LIBQEMU_CXL_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))

. ${LIBQEMU_CXL_ROOT}/liblog.sh
