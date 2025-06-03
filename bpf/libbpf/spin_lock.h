#pragma once

struct spin_lock_hmap_elem {
	struct bpf_spin_lock lock;
	int var[2];
};
