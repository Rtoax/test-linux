#pragma once
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_helpers.h>

#if defined(DEBUG)
#define BPF_DEBUG(fmt...) bpf_printk(fmt)
#else
#pragma message("You could $ make DEBUG=1 to enable debug info")
#define BPF_DEBUG(fmt...)
#endif
