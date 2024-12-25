/**
 * BPF_MAP_TYPE_ARRAY_OF_MAPS
 *
 * The array of maps map type contains references to other maps.
 *
 * This map type is a map-in-map type. The map values contain references to
 * other BPF maps. We will refer to map-in-map as the "outer map" and the maps
 * referenced as the "inner map(s)". The key advantage of using a map-in-map
 * is that the outer map is directly referenced by any programs that use it,
 * but the inner maps are not.
 */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_endian.h>

struct map_array_t {
	__uint(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, long);
	__uint(max_entries, 256);
} inner_map SEC(".maps");

struct {
#if defined(MAP_ARRAY_OF_MAPS)
	__uint(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
#elif defined(MAP_HASH_OF_MAPS)
	__uint(type, BPF_MAP_TYPE_HASH_OF_MAPS);
#endif
	__type(key, int);
	__type(value, int);
	__uint(max_entries, 1);
	__array(values, struct map_array_t);
} outer_map SEC(".maps");

char __license[] SEC("license") = "GPL";
