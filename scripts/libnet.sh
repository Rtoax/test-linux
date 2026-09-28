#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao. All rights reserved.
declare LIBNET_VERSION="v0.0.1"

get_free_tcp_port() {
	python3 -c "import socket;s=socket.socket();s.bind(('', 0));print(s.getsockname()[1]);s.close()"
}
