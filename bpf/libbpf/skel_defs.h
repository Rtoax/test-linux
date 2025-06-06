#ifndef NAME
#error Must define NAME, like '#define NAME tracepoint'
#endif

/* see also /usr/include/sys/cdefs.h __CONCAT() */
#define ___________CONCAT(a, b) a ## b
#define _____CONCAT(a, b) ___________CONCAT(a, b)

#define struct_bpf        _____CONCAT(NAME, _bpf)
#define _bpf__open_opts   _____CONCAT(NAME, _bpf__open_opts)
#define _bpf__open   _____CONCAT(NAME, _bpf__open)
#define _bpf__load        _____CONCAT(NAME, _bpf__load)
#define _bpf__open_and_load _____CONCAT(NAME, _bpf__open_and_load)
#define _bpf__attach      _____CONCAT(NAME, _bpf__attach)
#define _bpf__destroy     _____CONCAT(NAME, _bpf__destroy)
