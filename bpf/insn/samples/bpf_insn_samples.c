#include <stdio.h>
#include "bpf_insn_samples.h"

struct bpf_insn_sample {
	const char name[64];
	bpf_samples_get_insns_fn get_insns;
};

#define ARRAY_SIZE(arr)	(sizeof(arr) / sizeof(arr[0]))

static struct bpf_insn_sample samples[] = {
#define SAMPLE(sample) { .name = #sample, .get_insns = BPF_INSN_SAMPLE_FUNC_NAME(sample), }
	SAMPLE(trace_printk),
	SAMPLE(strncmp),
	SAMPLE(loop),
	SAMPLE(cgroup_from_id),
	SAMPLE(task_from_pid),
	SAMPLE(cgrp_storage_get),
	SAMPLE(get_func_ip),
};

bpf_samples_get_insns_fn bpf_samples_get_insns_from_string(const char *helper_str)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(samples); i++) {
		if (!strcmp(helper_str, samples[i].name))
			return samples[i].get_insns;
	}
	fprintf(stderr, "ERROR: not found bpf insns sample.\n");
	return NULL;
}
