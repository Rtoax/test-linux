// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
#pragma once

typedef struct id_handle_st {
	void *root;
#define ID_CMP_ASCENDING_ORDER ((void *)1)
#define ID_CMP_DESCENDING_ORDER ((void *)2)
	int (*id_cmp)(const void *pa, const void *pb);
} *id_handle_t;

struct id_handler {
	long id;
	/**
	 * handler return will pass to handle_id()
	 */
	int (*handler)(long id, void *arg);
	/**
	 * In addition to serving as a parameter for `handler()`, `arg` can be
	 * used for other purposes; for instance, an address can be stored in
	 * `arg` during registration, and later retrieved via the `id_handler`
	 * structure (found by looking up the ID) to make use of that `arg`.
	 */
	void *arg;
};

id_handle_t id_default_root(void);

id_handle_t create_id_handler(int (*id_cmp)(const void *, const void *));

struct id_handler *register_id(id_handle_t handle, long id,
			       int (*handler)(long, void *), void *arg);
int unregister_id(id_handle_t handle, long id);

struct id_handler *find_id_handler(id_handle_t handle, long id);
int handle_id(id_handle_t handle, long id);

int for_each_id(id_handle_t handle,
		void (*fn)(const struct id_handler *, void *arg), void *fn_arg);

void release_id_handle(id_handle_t handle);
