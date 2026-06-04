// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once

struct key_handler {
	int key;
	void *arg;
	void (*handler)(int key, void *arg);
};
