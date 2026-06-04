// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once

typedef void (*key_handler_fn)(int key, void *arg);

struct key_handler {
	int key;
	void *arg;
	key_handler_fn handler;
};

int keyboard_init(void);
int register_key_handler(int key, void *arg, key_handler_fn handler);
int exec_key_handler(int key);
