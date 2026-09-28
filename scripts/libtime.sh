#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao. All rights reserved.
declare LIBTIME_VERSION="v0.0.1"

get_nsecs() {
	date +%s%9N
}
