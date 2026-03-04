include bpf/bpftrace.mk
subdir-y := samples
subdir-y += scripts
target-shell-y := version.sh version.sh.1 version.sh.2 version.sh.3

SHELL_ARGS_version.sh.1 := --major
SHELL_ARGS_version.sh.2 := --minor
SHELL_ARGS_version.sh.3 := --patchlevel

include main.mk
