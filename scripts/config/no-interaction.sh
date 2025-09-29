#!/bin/bash
# Copyright (C) 2025 Rong Tao. All rights reserved.
#

readonly REAL_ROOT=$(dirname `realpath $0`)

. ${REAL_ROOT}/log.sh
. ${REAL_ROOT}/config.sh

write_configs_to_file .config
