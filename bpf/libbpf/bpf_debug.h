#pragma once
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_helpers.h>

#if defined(DEBUG)
#define BPF_DEBUG(fmt...) bpf_printk(fmt)
#else
#define BPF_DEBUG(fmt...)
#endif
