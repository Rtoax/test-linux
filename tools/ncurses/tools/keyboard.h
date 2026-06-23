// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once

struct keyboard {
	struct {
		unsigned long total;
		unsigned long left, right, up, down;
		unsigned long enter;
		unsigned long h, l, r, t, v;
	} cnt;
	int current_key; /* read from STDIN/getch() or /dev/tty */

#define KEYBOARD_INF0_FMT \
	"key(left=%ld,right=%ld,up=%ld,down=%ld,l=%ld,r=%ld,h=%ld,v=%ld,t=%ld,enter=%ld cnt=%ld,cur=%d=0x%x='%s')"
#define KEYBOARD_INF0_ARG(kb)                                              \
	kb->cnt.left, kb->cnt.right, kb->cnt.up, kb->cnt.down, kb->cnt.l,  \
		kb->cnt.r, kb->cnt.h, kb->cnt.v, kb->cnt.t, kb->cnt.enter, \
		kb->cnt.total, kb->current_key, kb->current_key,           \
		keyname(kb->current_key)
};

typedef void (*key_handler_fn)(int key, void *arg);

struct key_handler {
	int key;
	void *arg;
	key_handler_fn handler;
};

int keyboard_init(struct keyboard *k);
int register_key_handler(int key, void *arg, key_handler_fn handler);
int exec_key_handler(int key);
