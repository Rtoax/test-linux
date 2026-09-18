fentry
======

- `CONFIG_HAVE_FENTRY`
- gcc `-pg -mfentry`
- `fentry` + `BPF trampoline` ~= `kprobe hook`
- better performance than kprobe hook
