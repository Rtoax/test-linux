# SPDX-License-Identifier: GPL-3.0
${OUTPUT}config-map.o: ${OUTPUT}config-map.skel.h
${OUTPUT}socket_filter.o: ${OUTPUT}map_array.skel.h ${OUTPUT}socket_filter.skel.h
${OUTPUT}ring_buffer.o: ${OUTPUT}map_array.skel.h ${OUTPUT}ring_buffer.skel.h
${OUTPUT}tc.o: ${OUTPUT}tc.skel.h
${OUTPUT}rbtree.o: rbtree.h ${OUTPUT}rbtree.skel.h
${OUTPUT}rbtree-raw-map.o: ${OUTPUT}rbtree-raw-map.skel.h
${OUTPUT}spin_lock.o: ${OUTPUT}spin_lock.skel.h
${OUTPUT}xdp.o: ${OUTPUT}xdp.skel.h
${OUTPUT}xdp_simple.o: ${OUTPUT}xdp_simple.skel.h
${OUTPUT}xdp_dos.o: ${OUTPUT}xdp_dos.skel.h
${OUTPUT}xdp_devmap.o: ${OUTPUT}xdp_devmap.skel.h
${OUTPUT}xdp_cpumap.o: ${OUTPUT}xdp_cpumap.skel.h
${OUTPUT}xdp_xskmap.o: ${OUTPUT}xdp_xskmap.skel.h
${OUTPUT}sockops.o: ${OUTPUT}sockops.skel.h
${OUTPUT}kprobe.o: ${OUTPUT}kprobe.skel.h
${OUTPUT}tracepoint.o: ${OUTPUT}tracepoint.skel.h ${OUTPUT}map_hash.skel.h
${OUTPUT}raw_tracepoint.o: ${OUTPUT}raw_tracepoint.skel.h
${OUTPUT}tp_btf.o: ${OUTPUT}tp_btf.skel.h
${OUTPUT}perf_event.o: ${OUTPUT}perf_event.skel.h
${OUTPUT}perf_buffer.o: ${OUTPUT}perf_buffer.skel.h
${OUTPUT}sk_skb.o: ${OUTPUT}sk_skb.skel.h
${OUTPUT}sk_msg.o: ${OUTPUT}sk_msg.skel.h
${OUTPUT}cgroup_device.o: ${OUTPUT}cgroup_device.skel.h
${OUTPUT}cgroup_sysctl.o: ${OUTPUT}cgroup_sysctl.skel.h
${OUTPUT}fentry.o: ${OUTPUT}fentry.skel.h
${OUTPUT}fmod_ret.o: ${OUTPUT}fmod_ret.skel.h
${OUTPUT}iter_task.o: ${OUTPUT}iter_task.skel.h
${OUTPUT}iter_task_file.o: ${OUTPUT}iter_task_file.skel.h
${OUTPUT}iter_task_vma.o: ${OUTPUT}iter_task_vma.skel.h
${OUTPUT}iter_bpf_map.o: ${OUTPUT}iter_bpf_map.skel.h
${OUTPUT}iter_kmem_cache.o: ${OUTPUT}iter_kmem_cache.skel.h
${OUTPUT}lsm_bpf.o: ${OUTPUT}lsm_bpf.skel.h
${OUTPUT}lsm_file_open.bpf.o: lsm_file_open.bpf.c
${OUTPUT}lsm_file_open.o: ${OUTPUT}lsm_file_open.skel.h
${OUTPUT}lsm_file_open.skel.h: ${OUTPUT}lsm_file_open.bpf.o
${OUTPUT}lsm_socket_create.o: ${OUTPUT}lsm_socket_create.skel.h
${OUTPUT}lsm_socket_sendmsg.o: ${OUTPUT}lsm_socket_sendmsg.skel.h
${OUTPUT}map_hash.o: ${OUTPUT}map_hash.skel.h
${OUTPUT}map_percpu_hash.o: ${OUTPUT}map_percpu_hash.skel.h
${OUTPUT}map_lru_hash.o: ${OUTPUT}tracepoint.skel.h
${OUTPUT}map_lru_percpu_hash.o: ${OUTPUT}tracepoint.skel.h
${OUTPUT}map_array.o: ${OUTPUT}map_array.skel.h
${OUTPUT}map_percpu_array.o: ${OUTPUT}map_percpu_array.skel.h
${OUTPUT}map_prog_array.o: ${OUTPUT}map_prog_array.skel.h
